#include "output.h"
#include "esphome/core/log.h"

namespace esphome {
namespace max6966 {

static const char *const TAG = "max6966.output";

void MAX6966Output::setup() {
  // Configure the current setting for this output
  this->parent_->set_port_current(this->channel_, this->full_current_);

  // Turn off initially
  this->turn_off();
}

void MAX6966Output::dump_config() {
  ESP_LOGCONFIG(TAG, "MAX6966 Output:");
  ESP_LOGCONFIG(TAG, "  Channel: %d", this->channel_);
  ESP_LOGCONFIG(TAG, "  Current: %s", this->full_current_ ? "full (20mA)" : "half (10mA)");
}

void MAX6966Output::write_state(float state) {
  if (this->parent_ == nullptr) {
    return;
  }

  // Convert float (0.0-1.0) to PWM value (0x00-0xFF)
  // 0x00 = logic low (off)
  // 0x01 = logic high (input/high-Z)
  // 0x02 = constant current static (100%)
  // 0x03-0xFE = PWM duty cycle (3/256 to 254/256)
  // 0xFF = high-Z (off)

  uint8_t value;

  if (state <= 0.0f) {
    // Turn off - use high-Z state
    value = MAX6966_PORT_OFF;
  } else if (state >= 1.0f) {
    // Full brightness - use constant current static
    value = MAX6966_PORT_CONSTANT_CURRENT;
  } else {
    // PWM mode - map 0.0-1.0 to 0x03-0xFE (3/256 to 254/256)
    // This gives us 252 steps of PWM control
    uint16_t pwm_value = static_cast<uint16_t>(state * 252.0f) + 3;
    value = static_cast<uint8_t>(pwm_value);
  }

  this->parent_->set_port(this->channel_, value);
}

}  // namespace max6966
}  // namespace esphome
