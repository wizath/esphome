# ADDRSPI Component Concept

## Overview

A generic SPI multiplexer/demultiplexer component that uses address pins to select between multiple SPI devices sharing a single SPI bus. The component automatically calculates the maximum number of channels based on the number of address pins provided.

## Concept

The ADDRSPI component acts as a virtual SPI bus that routes SPI transactions to physical SPI devices through address-based channel selection. Each channel is selected by setting a unique binary pattern on the address pins.

### Key Features

- **Dynamic Channel Calculation**: Automatically determines channel count as 2^N where N = number of address pins
- **Transparent Operation**: SPI devices connected through ADDRSPI are unaware of the multiplexing
- **Flexible Configuration**: Supports 1-8 address pins (2 to 256 channels)
- **Hardware Agnostic**: Works with any decoder/demultiplexer chip (74HC138, CD4051B, CD4067, etc.)

## Configuration

### Basic Configuration

```yaml
addrspi:
  id: spi_mux
  spi_id: spi_bus
  address_pins: [25, 26, 27, 32, 33, 34]  # SPI_AD[5:0] - 6 pins = 64 channels
  channels:
    - bus_id: device_ch0
      channel: 0
    - bus_id: device_ch1
      channel: 1
    - bus_id: device_ch63
      channel: 63
```

### Configuration Parameters

| Parameter | Type | Required | Description |
|-----------|------|----------|-------------|
| `id` | ID | Yes | Component identifier |
| `spi_id` | SPI Bus ID | Yes | Parent SPI bus to multiplex |
| `address_pins` | GPIO List | Yes | List of GPIO pins for address selection (1-8 pins) |
| `channels` | List | Yes | List of virtual SPI bus channels |
| `channels[].bus_id` | ID | Yes | Identifier for the virtual SPI bus |
| `channels[].channel` | Integer | Yes | Channel number (0 to 2^N-1) |

## Examples

### 3 Address Pins (8 Channels) - Classic 74HC138

```yaml
spi:
  id: spi_bus
  clk_pin: GPIO14
  mosi_pin: GPIO13
  miso_pin: GPIO12

addrspi:
  id: mux_8ch
  spi_id: spi_bus
  address_pins: [GPIO2, GPIO4, GPIO16]  # A0, A1, A2
  channels:
    - bus_id: ch0
      channel: 0
    - bus_id: ch7
      channel: 7

# Devices connected through multiplexer
max6966:
  - id: led_driver_0
    spi_id: ch0
    cs_pin: GPIO15

  - id: led_driver_7
    spi_id: ch7
    cs_pin: GPIO15
```

### 6 Address Pins (64 Channels) - Large System

```yaml
spi:
  id: main_spi
  clk_pin: GPIO14
  mosi_pin: GPIO13
  miso_pin: GPIO12

addrspi:
  id: large_mux
  spi_id: main_spi
  address_pins: [25, 26, 27, 32, 33, 34]  # SPI_AD[5:0]
  channels:
    - bus_id: sensor_ch0
      channel: 0
    - bus_id: sensor_ch15
      channel: 15
    - bus_id: led_ch32
      channel: 32
    - bus_id: display_ch63
      channel: 63

# Multiple device types on different channels
mmc5983:
  id: magnetometer
  spi_id: sensor_ch0
  cs_pin: GPIO15

max6966:
  id: leds
  spi_id: led_ch32
  cs_pin: GPIO15

# Display on channel 63
display:
  - platform: st7789v
    spi_id: display_ch63
    cs_pin: GPIO15
```

### 4 Address Pins (16 Channels) - Medium System

```yaml
addrspi:
  id: mux_16ch
  spi_id: spi_bus
  address_pins: [GPIO23, GPIO22, GPIO21, GPIO19]  # A0-A3
  channels:
    - bus_id: ch0
      channel: 0
    - bus_id: ch8
      channel: 8
    - bus_id: ch15
      channel: 15
```

## Technical Architecture

### Channel Selection Logic

For N address pins, the component:
1. Calculates max channels: `max_channels = 2^N`
2. Validates channel numbers: `0 ≤ channel < max_channels`
3. Converts channel number to binary representation
4. Sets each address pin to corresponding bit value

**Example with 6 pins (64 channels):**
- Channel 0: `000000b` → All pins LOW
- Channel 1: `000001b` → Pin[0]=HIGH, others LOW
- Channel 42: `101010b` → Pin[5]=1, Pin[4]=0, Pin[3]=1, Pin[2]=0, Pin[1]=1, Pin[0]=0
- Channel 63: `111111b` → All pins HIGH

### SPI Delegate Pattern

The component uses a decorator pattern to intercept SPI transactions:

```
SPI Device → ADDRSPI Channel → ADDRSPI Delegate → Address Selection → Physical SPI Bus
```

**Transaction Flow:**
1. Device calls `spi->begin_transaction()`
2. ADDRSPI delegate intercepts call
3. Sets address pins to select correct channel
4. Waits for signal settling (1ms)
5. Forwards transaction to physical SPI bus
6. Device completes transaction normally

### Memory Usage

- **Address Pins Storage**: `N × sizeof(GPIOPin*)` = N × 4-8 bytes
- **Example (6 pins)**: 24-48 bytes depending on architecture
- **Impact**: Negligible on ESP32/ESP8266/RP2040

### Performance

- **Address Selection Overhead**: ~N microseconds for N pins
- **Settling Delay**: 1ms (hardware requirement)
- **Total Overhead**: ~1ms per transaction
- **Impact**: Negligible for typical SPI operations

## Hardware Considerations

### Compatible Decoder/Demultiplexer Chips

| Chip | Address Pins | Channels | Type |
|------|--------------|----------|------|
| 74HC138 | 3 | 8 | 3-to-8 decoder |
| 74HC238 | 3 | 8 | 3-to-8 decoder (inverted) |
| CD4051B | 3 | 8 | 8-channel analog mux/demux |
| CD4052B | 4 (2×2) | 8 | Dual 4-channel mux/demux |
| CD4067B | 4 | 16 | 16-channel analog mux/demux |
| 74HC4067 | 4 | 16 | 16-channel analog mux/demux |
| Custom | 1-8 | 2-256 | Any decoder logic |

### Wiring Example (6 pins, 64 channels)

```
ESP32           Decoder Logic           SPI Devices
GPIO25 ────────► AD0 ─┐
GPIO26 ────────► AD1 ─┤
GPIO27 ────────► AD2 ─┤ Binary    ┌──► CS0 (Channel 0)
GPIO32 ────────► AD3 ─┤ Decoder   ├──► CS1 (Channel 1)
GPIO33 ────────► AD4 ─┤ Logic     ├──► ...
GPIO34 ────────► AD5 ─┘           └──► CS63 (Channel 63)

SPI Bus (CLK, MOSI, MISO, CS) ────────► Shared across all devices
```

### CS Pin Handling

The CS pin is **shared** across all multiplexed devices:
- Single CS pin connects to all devices
- Decoder routes CS signal to correct device based on address pins
- ESPHome pin conflict validation disabled for multiplexer scenarios

## Implementation Details

### Python Configuration Schema

```python
CONF_ADDRESS_PINS = "address_pins"

def validate_channels(config):
    """Validate channel numbers based on address pin count."""
    num_pins = len(config[CONF_ADDRESS_PINS])
    max_channel = (2 ** num_pins) - 1

    for channel_conf in config.get(CONF_CHANNELS, []):
        channel_num = channel_conf[CONF_CHANNEL]
        if channel_num > max_channel:
            raise cv.Invalid(
                f"Channel {channel_num} exceeds maximum {max_channel} "
                f"for {num_pins} address pins"
            )
    return config

CONFIG_SCHEMA = cv.All(
    cv.Schema({
        cv.GenerateID(): cv.declare_id(ADDRSPIComponent),
        cv.Required(CONF_ADDRESS_PINS): cv.All(
            cv.ensure_list(pins.gpio_output_pin_schema),
            cv.Length(min=1, max=8),
        ),
        cv.Optional(CONF_CHANNELS, default=[]): cv.ensure_list({
            cv.Required(CONF_BUS_ID): cv.declare_id(ADDRSPIChannel),
            cv.Required(CONF_CHANNEL): cv.positive_int,
        }),
    })
    .extend(spi.spi_device_schema(cs_pin_required=False))
    .extend(cv.COMPONENT_SCHEMA),
    validate_channels,
)
```

### C++ Class Structure

```cpp
class ADDRSPIComponent : public Component, public spi::SPIDevice {
 public:
  void set_address_pins(std::vector<GPIOPin *> pins) {
    address_pins_ = std::move(pins);
    max_channel_ = (1 << address_pins_.size()) - 1;
  }

  void setup() override;
  void dump_config() override;
  void select_channel(uint8_t channel);

  uint8_t get_max_channel() const { return max_channel_; }

 protected:
  std::vector<GPIOPin *> address_pins_;
  uint8_t max_channel_{0};
  uint8_t current_channel_{255};  // Invalid = force first selection
};

class ADDRSPIChannel : public spi::SPIComponent {
 public:
  void set_parent(ADDRSPIComponent *parent) { parent_ = parent; }
  void set_channel(uint8_t channel) { channel_ = channel; }

  spi::SPIDelegate *register_device(...) override;

 protected:
  ADDRSPIComponent *parent_{nullptr};
  uint8_t channel_{0};
};

class ADDRSPIDelegate : public spi::SPIDelegate {
 public:
  void begin_transaction() override {
    parent_->select_channel(channel_);
    delegate_->begin_transaction();
  }
  // ... other SPI delegate methods

 protected:
  ADDRSPIComponent *parent_;
  uint8_t channel_;
  spi::SPIDelegate *delegate_;
};
```

### C++ Channel Selection Implementation

```cpp
void ADDRSPIComponent::select_channel(uint8_t channel) {
  if (channel > max_channel_) {
    ESP_LOGE(TAG, "Invalid channel %d (max: %d)", channel, max_channel_);
    return;
  }

  if (channel == current_channel_) {
    return;  // Already selected
  }

  ESP_LOGI(TAG, "Selecting channel %d", channel);
  current_channel_ = channel;

  // Set each address pin based on channel's binary representation
  for (size_t i = 0; i < address_pins_.size(); i++) {
    uint8_t bit_value = (channel >> i) & 1;
    address_pins_[i]->digital_write(bit_value);
  }

  delay(1);  // Signal settling time
}
```

## Use Cases

### 1. LED Matrix Control (64 MAX6966 drivers)
Control 640 LEDs (64 drivers × 10 ports) using 6 address pins + 1 shared SPI bus

### 2. Multi-Sensor Array
Connect 16 different sensor types on a single SPI bus using 4 address pins

### 3. Display Bank
Control multiple SPI displays (TFT, OLED, E-ink) with individual addressing

### 4. Industrial Control Systems
Interface with numerous SPI peripherals in factory automation

### 5. Data Acquisition
Multiplex between multiple ADC/DAC chips for high-channel-count systems

## Benefits vs Alternatives

### ADDRSPI vs Multiple SPI Buses
- ✅ Saves GPIO pins (6 address pins vs 16+ CS pins for 64 devices)
- ✅ Unified SPI configuration
- ✅ No hardware SPI bus limitations
- ⚠️ Slight overhead (~1ms per transaction)

### ADDRSPI vs Software CS Multiplexing
- ✅ Hardware-based routing (more reliable)
- ✅ Automatic channel management
- ✅ Transparent to devices
- ✅ Standard ESPHome patterns

### ADDRSPI vs I2C
- ✅ Higher speed (SPI typically faster than I2C)
- ✅ More device support (many chips SPI-only)
- ✅ Better for displays and high-bandwidth devices
- ⚠️ Requires more pins than I2C address-based multiplexing

## Limitations

1. **Shared Bandwidth**: All devices share single SPI bus bandwidth
2. **Sequential Access**: Only one device accessible at a time
3. **Settling Time**: 1ms overhead per channel switch
4. **Hardware Required**: Needs external decoder/demultiplexer chip
5. **CS Pin Sharing**: All devices must tolerate shared CS (most do)

## Future Enhancements

1. **Configurable Settling Delay**: Allow users to adjust based on hardware
2. **Channel Caching**: Skip address selection if already on correct channel (already implemented)
3. **Statistics**: Track channel usage and switch counts
4. **Power Management**: Disable unused channels
5. **Cascading**: Support multiple ADDRSPI components for 100+ channels

## Comparison to HC138 Component

This ADDRSPI concept is a generalization of the HC138 component:

| Feature | HC138 | ADDRSPI |
|---------|-------|---------|
| Address Pins | Fixed 3 (a0, a1, a2) | Variable 1-8 |
| Channels | Fixed 8 | Dynamic 2-256 |
| Configuration | Individual pins | Pin list |
| Hardware Support | 74HC138 specific | Generic decoders |
| Channel Calc | Hardcoded | Automatic |

**Migration Path**: HC138 users can migrate to ADDRSPI by changing:
```yaml
# Old HC138
a0: GPIO2
a1: GPIO4
a2: GPIO16

# New ADDRSPI
address_pins: [GPIO2, GPIO4, GPIO16]
```

## Conclusion

ADDRSPI provides a flexible, scalable solution for SPI bus multiplexing that adapts to different hardware requirements. By automatically calculating channel count from address pin count, it simplifies configuration while supporting systems from 2 to 256 channels with a single, unified approach.
