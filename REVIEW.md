# MAX11210 ESPHome Driver Review (vs. Datasheet)

## SPI Protocol -- PASS

- SPI MODE 0 (CPOL=0, CPHA=0) matches datasheet: "Clock in data at DIN on the rising edge of SCLK", "Data at RDY/DOUT changes on the falling edge of SCLK"
- MSB first, 4MHz clock (under 5MHz max) -- correct
- CS active-low handled by ESPHome SPI framework

## Command Byte Construction -- PASS

MODE=0 (conversion/calibration):
- `send_command_` builds `0x80 | cmd`. Self-cal = `0x80 | 0x10` = 0x90 matches Table 8 (`10010000`).
- Convert 10sps = `0x80 | 0x03` = 0x83 matches Table 8 (`10000011`).

MODE=1 (register access):
- `0xC0 | (reg << 1) | R/W` correctly encodes Table 6: `START=1|MODE=1|0|RS3|RS2|RS1|RS0|W/R`
- Verified for STAT1(0x0), CTRL1(0x1), DATA(0x4), SCGC(0x8) -- all correct.

## Register Bit Definitions -- PASS

All CTRL1 bits match Table 12:
- LINEF=B7(0x80), U/B=B6(0x40), EXTCLK=B5(0x20), REFBUF=B4(0x10), SIGBUF=B3(0x08), FORMAT=B2(0x04), SCYCLE=B1(0x02)

All CTRL3 bits match Table 14:
- DGAIN[2:0]=B7-B5, NOSYSG=B4(0x10), NOSYSO=B3(0x08), NOSCG=B2(0x04), NOSCO=B1(0x02)

STAT1 RDY=B0(0x01) matches Table 11.

## LINEF Polarity -- PASS

Datasheet: "LINEF=1 to select data rates for 50Hz power mains". Driver: `if (line_50hz_) ctrl1 |= CTRL1_LINEF`. Correct.

## U/B Polarity -- PASS

Datasheet: "A 1 in this bit location selects a unipolar input range". Driver: `if (!bipolar_) ctrl1 |= CTRL1_UB`. Correct.

## RDY Bit Polarity -- PASS

Datasheet Table 11: "RDY ready bit is set to 1 to indicate that a conversion result is available." Driver checks `stat & STAT1_RDY`. Correct. (Note: the RDY/DOUT *pin* has inverse logic -- low=ready -- but we read the STAT1 register bit, not the pin.)

## Voltage Conversion Math -- PASS

Bipolar two's complement (Table 16b):
- 0x800000 (-8388608) = -VREF, 0x000000 = 0V, 0x7FFFFF (+8388607) = +VREF
- Driver: `raw / 8388608.0 * (vref / gain)` -- correct

Unipolar straight binary (Table 16a):
- 0x000000 = 0V, 0xFFFFFF = VREF
- Driver: `(raw & 0x00FFFFFF) / 16777216.0 * (vref / gain)` -- correct
- Sign extension from `read_register24_` is properly masked away

Digital gain applied correctly: input range = VREF/gain, full-scale digital output maps to VREF/gain.

## Conversion Timeouts -- PASS

All timeouts cover worst-case LINEF=1 (50Hz) rates with margin:
- 1SPS: 1200ms (need 1200ms for 0.833sps at LINEF=1)
- 2.5SPS: 500ms (need 480ms)
- 5SPS: 250ms (need 240ms)
- etc.

## Self-Calibration Sequence -- PASS (with one bug below)

Matches Table 3a steps:
1. Enable self-cal registers (NOSCG=0, NOSCO=0) via CTRL3 write
2. Send self-cal command 0x90
3. Wait 300ms (datasheet: 200ms required)

---

## BUG: CTRL3 enables self-cal registers even when self_calibrate=false

**File:** `max11210.cpp:103`

```cpp
uint8_t ctrl3 = CTRL3_NOSYSO | CTRL3_NOSYSG;  // = 0x18
```

This always sets NOSCG=0 and NOSCO=0, enabling self-calibration registers. But when `self_calibrate=false`, no calibration is performed, so SCOC and SCGC contain their POR defaults (0x000000).

Datasheet p.9: "The devices power up with the internal calibration registers disabled, and therefore a full-scale input produces a result of 60% of the full-scale digital range. To use the full-scale digital range, a calibration must be performed."

The POR default for CTRL3 is 0x1E (NOSYSG=1, NOSYSO=1, NOSCG=1, NOSCO=1 -- all disabled). With all calibration disabled, 60% output is expected. But the driver *enables* the self-cal registers with their zero values, which will produce wrong results -- effectively zero gain correction from SCGC=0x000000.

**Fix:** Only clear NOSCG/NOSCO when self_calibrate is true:

```cpp
uint8_t ctrl3 = CTRL3_NOSYSO | CTRL3_NOSYSG;
if (this->self_calibrate_) {
  // Enable self-cal registers (clear NOSCG and NOSCO)
} else {
  // Keep self-cal registers disabled (match POR default)
  ctrl3 |= CTRL3_NOSCG | CTRL3_NOSCO;
}
ctrl3 |= (this->gain_ << CTRL3_DGAIN_SHIFT);
```

## MINOR: No OR/UR flag check in read_data_

**File:** `max11210.cpp:178-186`

STAT1 has OR (overrange, B3) and UR (underrange, B2) flags. When set, the conversion result is clipped to min/max. Driver reads STAT1 but only checks RDY. Logging OR/UR would help diagnose clipping during development.

## MINOR: No communication check in setup()

**File:** `max11210.cpp:116`

After setup, STAT1 is read and logged but no error is raised if the value is 0xFF (disconnected device). Should call `this->mark_failed()` if communication looks broken.

## MINOR: Unused import in sensor.py

**File:** `sensor.py:5`

`CONF_ID` is imported but never used.
