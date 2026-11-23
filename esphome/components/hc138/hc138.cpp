#include "esphome/core/log.h"
#include "hc138.h"

namespace esphome {
namespace hc138 {

static const char *TAG = "hc138";

spi::SPIDelegate *HC138Channel::register_device(spi::SPIClient *device, spi::SPIMode mode, spi::SPIBitOrder bit_order,
                                                uint32_t data_rate, GPIOPin *cs_pin, bool release_device,
                                                bool write_only) {
  if (parent_ == nullptr) {
    ESP_LOGE(TAG, "Parent not set for channel %d", channel_);
    return nullptr;
  }

  auto existing = this->devices_.find(device);
  if (existing != this->devices_.end())
    return existing->second;

  if (this->parent_->cs_ != nullptr)
    cs_pin = this->parent_->cs_;
  auto *delegate =
      this->parent_->parent_->register_device(device, mode, bit_order, data_rate, cs_pin, release_device, write_only);
  if (delegate == nullptr)
    return nullptr;
  auto *wrapper = new HC138SPIDelegate(this->channel_, this->parent_, delegate);
  this->devices_.emplace(device, wrapper);
  return wrapper;
}

void HC138Channel::unregister_device(spi::SPIClient *device) {
  if (this->devices_.count(device) == 0)
    return;
  spi::SPIComponent::unregister_device(device);
  this->parent_->parent_->unregister_device(device);
}

void HC138Component::setup() {
  a0_->setup();
  a1_->setup();
  a2_->setup();
  this->select_channel(0);
}

void HC138Component::select_channel(uint8_t channel) {
  ESP_LOGI(TAG, "selecting channel %d", channel);

  a0_->digital_write(channel & 0x01);
  a1_->digital_write((channel >> 1) & 0x01);
  a2_->digital_write((channel >> 2) & 0x01);
}

void HC138SPIDelegate::transfer(uint8_t *data, size_t length) { parent_delegate_->transfer(data, length); }

uint8_t HC138SPIDelegate::transfer(uint8_t data) { return parent_delegate_->transfer(data); }

void HC138SPIDelegate::write(uint16_t data, size_t bits) { parent_delegate_->write(data, bits); }

void HC138SPIDelegate::read_array(uint8_t *data, size_t length) { parent_delegate_->read_array(data, length); }

void HC138SPIDelegate::write_array(const uint8_t *data, size_t length) { parent_delegate_->write_array(data, length); }

void HC138SPIDelegate::begin_transaction() {
  parent_->select_channel(this->channel_);
  parent_delegate_->begin_transaction();
}

void HC138SPIDelegate::end_transaction() { parent_delegate_->end_transaction(); }

}  // namespace hc138
}  // namespace esphome
