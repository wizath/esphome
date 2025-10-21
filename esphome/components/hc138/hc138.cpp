#include "esphome/core/log.h"
#include "hc138.h"

namespace esphome {
namespace hc138 {

static const char *TAG = "hc138";

spi::SPIDelegate *HC138Channel::register_device(spi::SPIClient *device, spi::SPIMode mode, spi::SPIBitOrder bit_order,
                                                uint32_t data_rate, GPIOPin *cs_pin, bool release_device,
                                                bool write_only) {
  ESP_LOGI(TAG, "HC138: register_device called for channel %d", channel_);
  ESP_LOGI(TAG, "HC138: Using shared delegate for all channels");

  if (parent_ == nullptr) {
    ESP_LOGE(TAG, "HC138: Parent not set for channel %d", channel_);
    return nullptr;
  }

  if (parent_->shared_delegate_ == nullptr) {
    ESP_LOGE(TAG, "HC138: Shared delegate not set for channel %d", channel_);
    return nullptr;
  }

  ESP_LOGI(TAG, "HC138: Using shared delegate %p for channel %d", static_cast<void *>(parent_->shared_delegate_),
           channel_);
  return new HC138SPIDelegate(this->channel_, this->parent_, parent_->shared_delegate_);
}

void HC138Component::setup() {
  ESP_LOGI(TAG, "HC138: Setup starting...");
  ESP_LOGI(TAG, "HC138: CS pin pointer = %p", static_cast<void *>(this->cs_));

  a0_->setup();
  a1_->setup();
  a2_->setup();
  ESP_LOGI(TAG, "HC138: Address pins A0=%p, A1=%p, A2=%p setup complete", static_cast<void *>(a0_),
           static_cast<void *>(a1_), static_cast<void *>(a2_));

  // Setup and initialize CS pin if available
  if (this->cs_ != nullptr) {
    ESP_LOGI(TAG, "HC138: Setting up CS pin...");
    this->cs_->setup();
    this->cs_->digital_write(true);  // Initialize CS high (inactive)
    ESP_LOGI(TAG, "HC138: CS pin initialized and set high (inactive)");
  } else {
    ESP_LOGW(TAG, "HC138: No CS pin available - cs_ is nullptr");
  }

#ifdef HC138_USE_SHARED_DELEGATE
  // Create shared SPI delegate for all channels
  ESP_LOGI(TAG, "HC138: Creating shared SPI delegate");
  this->shared_delegate_ =
      this->parent_->register_device(this, this->mode_, this->bit_order_, this->data_rate_, nullptr, false, false);
  if (this->shared_delegate_ != nullptr) {
    ESP_LOGI(TAG, "HC138: Shared delegate created successfully: %p", static_cast<void *>(this->shared_delegate_));
  } else {
    ESP_LOGE(TAG, "HC138: Failed to create shared delegate");
  }
#endif

  ESP_LOGI(TAG, "HC138: Setup complete");
}

void HC138Component::select_channel(uint8_t channel) {
  ESP_LOGI(TAG, "HC138: Selecting channel %d (A0=%d, A1=%d, A2=%d)", channel, channel & 0x01, (channel >> 1) & 0x01,
           (channel >> 2) & 0x01);

  ESP_LOGD(TAG, "HC138: Setting address pins - A0:%s, A1:%s, A2:%s", (channel & 0x01) ? "HIGH" : "LOW",
           ((channel >> 1) & 0x01) ? "HIGH" : "LOW", ((channel >> 2) & 0x01) ? "HIGH" : "LOW");

  a0_->digital_write(channel & 0x01);
  a1_->digital_write((channel >> 1) & 0x01);
  a2_->digital_write((channel >> 2) & 0x01);

  // Control CS pin if available
  if (this->cs_ != nullptr) {
    ESP_LOGI(TAG, "HC138: Activating CS pin %p for channel %d", static_cast<void *>(this->cs_), channel);
    this->cs_->digital_write(false);  // Active low
  } else {
    ESP_LOGW(TAG, "HC138: No CS pin available for channel %d", channel);
  }

  ESP_LOGD(TAG, "HC138: Address pins set - Channel %d should be active now", channel);
}

void HC138SPIDelegate::transfer(uint8_t *data, size_t length) {
  ESP_LOGD(TAG, "HC138 SPI: Transfer %d bytes on channel %d", length, this->channel_);
  if (length > 0 && length <= 8) {
    std::string hex_data = "Data: ";
    for (size_t i = 0; i < length; i++) {
      char buf[8];
      sprintf(buf, "0x%02X ", data[i]);
      hex_data += buf;
    }
    ESP_LOGV(TAG, "HC138 SPI: %s", hex_data.c_str());
  }
  parent_delegate_->transfer(data, length);
}

uint8_t HC138SPIDelegate::transfer(uint8_t data) {
  ESP_LOGD(TAG, "HC138 SPI: Transfer 1 byte (0x%02X) on channel %d", data, this->channel_);
  uint8_t result = parent_delegate_->transfer(data);
  ESP_LOGD(TAG, "HC138 SPI: Received 0x%02X on channel %d", result, this->channel_);
  return result;
}

void HC138SPIDelegate::write(uint16_t data, size_t bits) {
  ESP_LOGD(TAG, "HC138 SPI: Write 0x%04X (%d bits) on channel %d", data, bits, this->channel_);
  parent_delegate_->write(data, bits);
}

void HC138SPIDelegate::read_array(uint8_t *data, size_t length) {
  ESP_LOGD(TAG, "HC138 SPI: Read %d bytes on channel %d", length, this->channel_);
  parent_delegate_->read_array(data, length);
  if (length > 0 && length <= 8) {
    std::string hex_data = "Data: ";
    for (size_t i = 0; i < length; i++) {
      char buf[8];
      sprintf(buf, "0x%02X ", data[i]);
      hex_data += buf;
    }
    ESP_LOGV(TAG, "HC138 SPI: %s", hex_data.c_str());
  }
}

void HC138SPIDelegate::write_array(const uint8_t *data, size_t length) {
  ESP_LOGD(TAG, "HC138 SPI: Write %d bytes on channel %d", length, this->channel_);
  if (length > 0 && length <= 8) {
    std::string hex_data = "Data: ";
    for (size_t i = 0; i < length; i++) {
      char buf[8];
      sprintf(buf, "0x%02X ", data[i]);
      hex_data += buf;
    }
    ESP_LOGV(TAG, "HC138 SPI: %s", hex_data.c_str());
  }
  parent_delegate_->write_array(data, length);
}

void HC138SPIDelegate::begin_transaction() {
  ESP_LOGI(TAG, "HC138 SPI: Starting transaction on channel %d, delegate=%p", this->channel_,
           static_cast<void *>(parent_delegate_));
  parent_->select_channel(this->channel_);
  ESP_LOGI(TAG, "HC138 SPI: Address pins set, beginning parent transaction");

  // Small delay to ensure address pins are stable
  delayMicroseconds(1);

  parent_delegate_->begin_transaction();
  ESP_LOGI(TAG, "HC138 SPI: Transaction started");
}

void HC138SPIDelegate::end_transaction() {
  ESP_LOGD(TAG, "HC138 SPI: Ending transaction on channel %d", this->channel_);
  parent_delegate_->end_transaction();

  // Deactivate CS pin if available
  if (parent_->cs_ != nullptr) {
    ESP_LOGI(TAG, "HC138: Deactivating CS pin %p for channel %d", static_cast<void *>(parent_->cs_), this->channel_);
    parent_->cs_->digital_write(true);  // Active low, so high = inactive
  } else {
    ESP_LOGW(TAG, "HC138: No CS pin available to deactivate for channel %d", this->channel_);
  }

  ESP_LOGD(TAG, "HC138 SPI: Transaction ended");
}

}  // namespace hc138
}  // namespace esphome
