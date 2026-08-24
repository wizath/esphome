#include "addrspi2.h"

#include "esphome/core/log.h"

#include <algorithm>
#include <cstring>

namespace esphome {
namespace addrspi2 {

static const char *const TAG = "addrspi2";

void ADDRSPI2Component::setup() { this->spi_setup(); }

void ADDRSPI2Component::dump_config() {
  ESP_LOGCONFIG(TAG, "ADDRSPI2:");
  LOG_PIN("  CS Pin: ", this->cs_);
  ESP_LOGCONFIG(TAG, "  Devices: %u", static_cast<unsigned>(this->devices_.size()));
  for (auto *device : this->devices_) {
    if (device != nullptr) {
      ESP_LOGCONFIG(TAG, "    Address: 0x%02X", device->get_address());
    }
  }
}

void ADDRSPI2Component::write_transaction(uint8_t address, const uint8_t *payload, size_t length) {
  if (payload == nullptr && length != 0) {
    ESP_LOGE(TAG, "Write payload is null");
    return;
  }

  uint8_t stack_buffer[STACK_PAYLOAD_SIZE + 1];
  if (length <= STACK_PAYLOAD_SIZE) {
    stack_buffer[0] = address;
    if (length != 0) {
      std::memcpy(&stack_buffer[1], payload, length);
    }
    this->enable();
    this->delegate_->write_array(stack_buffer, length + 1);
    this->disable();
    return;
  }

  std::vector<uint8_t> buffer(length + 1);
  buffer[0] = address;
  std::memcpy(&buffer[1], payload, length);
  this->enable();
  this->delegate_->write_array(buffer.data(), buffer.size());
  this->disable();
}

void ADDRSPI2Component::transfer_transaction(uint8_t address, const uint8_t *tx_payload, uint8_t *rx_payload,
                                             size_t length) {
  if ((tx_payload == nullptr || rx_payload == nullptr) && length != 0) {
    ESP_LOGE(TAG, "Transfer payload is null");
    return;
  }

  uint8_t stack_tx[STACK_PAYLOAD_SIZE + 1];
  uint8_t stack_rx[STACK_PAYLOAD_SIZE + 1];
  if (length <= STACK_PAYLOAD_SIZE) {
    stack_tx[0] = address;
    if (length != 0) {
      std::memcpy(&stack_tx[1], tx_payload, length);
    }
    this->enable();
    this->delegate_->transfer(stack_tx, stack_rx, length + 1);
    this->disable();
    if (length != 0) {
      std::memcpy(rx_payload, &stack_rx[1], length);
    }
    return;
  }

  std::vector<uint8_t> tx_buffer(length + 1);
  std::vector<uint8_t> rx_buffer(length + 1);
  tx_buffer[0] = address;
  std::memcpy(&tx_buffer[1], tx_payload, length);
  this->enable();
  this->delegate_->transfer(tx_buffer.data(), rx_buffer.data(), tx_buffer.size());
  this->disable();
  std::memcpy(rx_payload, &rx_buffer[1], length);
}

void ADDRSPI2Device::write_transaction(const uint8_t *payload, size_t length) {
  if (this->parent_ == nullptr) {
    ESP_LOGE(TAG, "ADDRSPI2 device 0x%02X has no parent", this->address_);
    return;
  }
  this->parent_->write_transaction(this->address_, payload, length);
}

void ADDRSPI2Device::transfer_transaction(const uint8_t *tx_payload, uint8_t *rx_payload, size_t length) {
  if (this->parent_ == nullptr) {
    ESP_LOGE(TAG, "ADDRSPI2 device 0x%02X has no parent", this->address_);
    return;
  }
  this->parent_->transfer_transaction(this->address_, tx_payload, rx_payload, length);
}

}  // namespace addrspi2
}  // namespace esphome
