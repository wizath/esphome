# AD9959 Driver Datasheet Review

## Scope

Reviewed `esphome/components/ad9959` against `ad9959.pdf` from Librarian. This is a targeted driver/datasheet review, not a hardware validation run.

## Datasheet Cross-Reference

- AD9959 has four DDS cores with independent frequency, phase, and amplitude control; each channel has a 32-bit FTW, 14-bit phase offset, and 10-bit amplitude multiplier. Datasheet lines 165, 171, 173.
- Serial writes use an instruction byte followed by a register-width data phase. Writes are registered on SCLK rising edges, and FR1 is a three-byte register. Datasheet lines 1475-1481, 1561.
- `CSR[7:4]` channel enable bits take effect immediately and do not require `I/O_UPDATE`; channel/profile registers share addresses and are selected through CSR. Datasheet lines 1469, 1510, 1811.
- `I/O_UPDATE` transfers serial buffer data into active registers; minimum pulse width is one `SYNC_CLK` period. Datasheet lines 502, 1434, 1442.
- PLL multiplier is a 5-bit value in `FR1[22:18]`; PLL output range is 100-500 MHz, with VCO gain low below 160 MHz and high above 255 MHz. Datasheet lines 825, 831, 1826.
- Manual amplitude mode is `ACR[12]=1` and `ACR[11]=0`; amplitude scale factor is `ACR[9:0]`. Datasheet lines 1295, 1299, 1964.

## Findings

### Fixed: `ref_clock * pll_multiplier` was not validated

`__init__.py` limits `pll_multiplier` to 4-20, but does not validate the resulting system clock. The datasheet restricts the PLL output to 100-500 MHz. A config such as `ref_clock: 30000000`, `pll_multiplier: 20` silently computes a 600 MHz core clock in `configure_pll_()`, producing invalid FTWs and out-of-spec hardware operation.

Status: fixed in `esphome/components/ad9959/__init__.py` by validating `ref_clock * pll_multiplier`.

### Fixed: `AD9959Channel::write_state()` did not clamp output state

`write_state()` directly converts `state * max_freq` to `uint32_t`. If an automation or lambda sends a value outside `0.0-1.0`, the frequency can exceed Nyquist or become an implementation-defined conversion edge case for negative/NaN values.

Status: fixed in `esphome/components/ad9959/ad9959.h` by clamping NaN/negative/over-range values before calculating frequency.

### Medium: `set_phase()` and `set_amplitude()` do not make values active

Both methods write buffered registers but do not call `update_registers()`. This is technically allowed, but it differs from `AD9959Channel::write_state()`, which updates immediately after frequency writes. Users calling the C++ API for phase/amplitude can think the command succeeded while the chip output remains unchanged until an explicit `I/O_UPDATE`.

Fix: either add an `auto_update` option or document that low-level setters are staged and require `update_registers()`.

### Low: unsupported output range is hardcoded to `core_clock / 2`

The output platform maps `level: 1.0` to Nyquist. Real usable sine output is usually kept below that for analog reconstruction/filtering reasons, and the example uses `x / 250000000.0` with a 500 MHz core. This is mathematically consistent with the FTW equation but not a conservative signal-quality default.

Fix: add an optional `max_frequency` per output channel and validate it against `core_clock / 2`.

## What Looks Correct

- Register addresses and lengths for CSR, FR1, FR2, CFR, CFTW, CPOW, ACR, LSRR, RDW, FDW, and CW1 match the datasheet register map subset used by the driver.
- FR1 PLL byte packing matches `FR1[22:18]` for multiplier and `FR1[23]` for VCO gain.
- CSR selection uses `CSR[7:4]` and preserves MSB-first, single-bit 3-wire mode.
- CFTW calculation uses `frequency * 2^32 / core_clock`, which matches the DDS tuning-word relationship.
- ACR manual amplitude uses `ACR[12]` and `ACR[9:0]`, matching the manual amplitude mode description.

## Recommendation

The remaining issues are API/documentation choices, but they should be made explicit because AD9959 register writes are buffered and `CSR` channel selection is immediate.
