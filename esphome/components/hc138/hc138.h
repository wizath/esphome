#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace hc138 {

class HC138Component;

// Custom SPI delegate that switches HC138 channel before each SPI operation
class HC138SPIDelegate : public spi::SPIDelegate {
 public:
  HC138SPIDelegate(HC138Component *parent, uint8_t channel, spi::SPIDelegate *delegate)
      : parent_(parent), channel_(channel), delegate_(delegate) {}

  void begin_transaction() override;
  void end_transaction() override;
  uint8_t transfer(uint8_t data) override;
  void transfer(uint8_t *ptr, size_t length) override;
  void transfer(const uint8_t *txbuf, uint8_t *rxbuf, size_t length) override;
  void write(uint16_t data, size_t num_bits) override;
  void write16(uint16_t data) override;
  void read_array(uint8_t *data, size_t length) override;

 protected:
  HC138Component *parent_;
  uint8_t channel_;
  spi::SPIDelegate *delegate_;
};

class HC138Channel : public spi::SPIComponent {
 public:
  HC138Channel() = default;

  void set_channel(uint8_t channel) { channel_ = channel; }
  void set_parent(HC138Component *parent) { parent_ = parent; }

  void setup() override {}
  void dump_config() override {}

  // Override register_device to return HC138-specific delegate
  spi::SPIDelegate *register_device(spi::SPIClient *device, spi::SPIMode mode, spi::SPIBitOrder bit_order,
                                    uint32_t data_rate, GPIOPin *cs_pin, bool release_device, bool write_only) override;

 protected:
  uint8_t channel_{0};
  HC138Component *parent_{nullptr};
};

class HC138Component : public Component,
                       public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW,
                                             spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_1KHZ> {
 public:
  HC138Component() = default;

  void set_a0(GPIOPin *pin) { a0_ = pin; }
  void set_a1(GPIOPin *pin) { a1_ = pin; }
  void set_a2(GPIOPin *pin) { a2_ = pin; }

  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::IO; }

  void select_channel(uint8_t channel);

 protected:
  GPIOPin *a0_{nullptr};
  GPIOPin *a1_{nullptr};
  GPIOPin *a2_{nullptr};
  uint8_t current_channel_{0};  // Default to channel 0

  friend class HC138Channel;
  friend class HC138SPIDelegate;
};

}  // namespace hc138
}  // namespace esphome
