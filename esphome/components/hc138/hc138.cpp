#include "esphome/core/log.h"
#include "hc138.h"

namespace esphome {
namespace hc138 {

static const char *TAG = "hc138";

void HC138Component::setup() {
  ESP_LOGI(TAG, "HC138 setup started");

  // Setup address pins
  if (a0_)
    a0_->setup();
  if (a1_)
    a1_->setup();
  if (a2_)
    a2_->setup();

  // Force initial channel selection by resetting current_channel_
  current_channel_ = 255;  // Invalid channel to force selection
  ESP_LOGI(TAG, "Initializing HC138 to channel 0");
  select_channel(0);

  ESP_LOGI(TAG, "HC138 setup complete");
}

void HC138Component::dump_config() {
  ESP_LOGCONFIG(TAG, "HC138:");
  LOG_PIN("  A0 Pin: ", a0_);
  LOG_PIN("  A1 Pin: ", a1_);
  LOG_PIN("  A2 Pin: ", a2_);
  ESP_LOGCONFIG(TAG, "  Current Channel: %d", current_channel_);
}

void HC138Component::select_channel(uint8_t channel) {
  ESP_LOGI(TAG, "select_channel called with channel %d, current_channel_ %d", channel, current_channel_);
  if (channel == current_channel_) {
    ESP_LOGI(TAG, "Already on channel %d, but forcing selection anyway", channel);
    // Continue anyway to show address pin changes
  }

  current_channel_ = channel;

  uint8_t a0_val = channel & 1;
  uint8_t a1_val = (channel >> 1) & 1;
  uint8_t a2_val = (channel >> 2) & 1;

  ESP_LOGI(TAG, "HC138 selecting channel %d (A0=%d, A1=%d, A2=%d)", channel, a0_val, a1_val, a2_val);

  if (a0_) {
    a0_->digital_write(a0_val);
    ESP_LOGI(TAG, "Set A0 pin to %d", a0_val);
  }
  if (a1_) {
    a1_->digital_write(a1_val);
    ESP_LOGI(TAG, "Set A1 pin to %d", a1_val);
  }
  if (a2_) {
    a2_->digital_write(a2_val);
    ESP_LOGI(TAG, "Set A2 pin to %d", a2_val);
  }

  // Small delay to let the signals settle
  delay(1);
}

// HC138SPIDelegate implementations
void HC138SPIDelegate::begin_transaction() {
  ESP_LOGI("hc138_delegate", "HC138 Channel %d: begin_transaction - activating CS pin", channel_);
  parent_->select_channel(channel_);
  delegate_->begin_transaction();
}

void HC138SPIDelegate::end_transaction() {
  ESP_LOGI("hc138_delegate", "HC138 Channel %d: end_transaction - deactivating CS pin", channel_);
  delegate_->end_transaction();
}

uint8_t HC138SPIDelegate::transfer(uint8_t data) {
  ESP_LOGI("hc138_delegate", "HC138 Channel %d: transferring 0x%02X", channel_, data);
  return delegate_->transfer(data);
}

void HC138SPIDelegate::transfer(uint8_t *ptr, size_t length) { delegate_->transfer(ptr, length); }

void HC138SPIDelegate::transfer(const uint8_t *txbuf, uint8_t *rxbuf, size_t length) {
  delegate_->transfer(txbuf, rxbuf, length);
}

void HC138SPIDelegate::write(uint16_t data, size_t num_bits) { delegate_->write(data, num_bits); }

void HC138SPIDelegate::write16(uint16_t data) { delegate_->write16(data); }

void HC138SPIDelegate::read_array(uint8_t *data, size_t length) { delegate_->read_array(data, length); }

spi::SPIDelegate *HC138Channel::register_device(spi::SPIClient *device, spi::SPIMode mode, spi::SPIBitOrder bit_order,
                                                uint32_t data_rate, GPIOPin *cs_pin, bool release_device,
                                                bool write_only) {
  ESP_LOGI(TAG, "HC138 Channel %d: registering SPI device", channel_);

  if (!parent_) {
    ESP_LOGE(TAG, "HC138 Channel %d: parent not set", channel_);
    return nullptr;
  }

  // Register device with the parent SPI bus (HC138Component's parent)
  auto *delegate =
      parent_->parent_->register_device(device, mode, bit_order, data_rate, cs_pin, release_device, write_only);
  if (!delegate) {
    ESP_LOGE(TAG, "HC138 Channel %d: failed to register device with parent SPI", channel_);
    return nullptr;
  }

  ESP_LOGI(TAG, "HC138 Channel %d: successfully registered, creating wrapper delegate", channel_);

  // Wrap the delegate in our HC138-specific delegate
  return new HC138SPIDelegate(parent_, channel_, delegate);
}

}  // namespace hc138
}  // namespace esphome
