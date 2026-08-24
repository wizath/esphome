#pragma once

#include "esphome/components/spi/spi.h"
#include "esphome/core/component.h"

#include <cstddef>
#include <vector>

namespace esphome {
namespace addrspi2 {

class ADDRSPI2Device;

class ADDRSPI2Component : public Component,
                          public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW,
                                                spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_1MHZ> {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  void register_device(ADDRSPI2Device *device) { this->devices_.push_back(device); }
  void write_transaction(uint8_t address, const uint8_t *payload, size_t length);
  void transfer_transaction(uint8_t address, const uint8_t *tx_payload, uint8_t *rx_payload, size_t length);

 protected:
  static const size_t STACK_PAYLOAD_SIZE = 16;

  std::vector<ADDRSPI2Device *> devices_;
};

class ADDRSPI2Device {
 public:
  void set_parent(ADDRSPI2Component *parent) { this->parent_ = parent; }
  void set_address(uint8_t address) { this->address_ = address; }

  uint8_t get_address() const { return this->address_; }
  void write_transaction(const uint8_t *payload, size_t length);
  void transfer_transaction(const uint8_t *tx_payload, uint8_t *rx_payload, size_t length);

 protected:
  ADDRSPI2Component *parent_{nullptr};
  uint8_t address_{0};
};

}  // namespace addrspi2
}  // namespace esphome
