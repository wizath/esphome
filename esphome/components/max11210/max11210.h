#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace max11210 {

enum Max11210Gain : uint8_t {
  MAX11210_GAIN_1 = 0x00,
  MAX11210_GAIN_2 = 0x01,
  MAX11210_GAIN_4 = 0x02,
  MAX11210_GAIN_8 = 0x03,
  MAX11210_GAIN_16 = 0x04,
};

enum Max11210Rate : uint8_t {
  MAX11210_RATE_1SPS = 0x00,
  MAX11210_RATE_2_5SPS = 0x01,
  MAX11210_RATE_5SPS = 0x02,
  MAX11210_RATE_10SPS = 0x03,
  MAX11210_RATE_15SPS = 0x04,
  MAX11210_RATE_30SPS = 0x05,
  MAX11210_RATE_60SPS = 0x06,
  MAX11210_RATE_120SPS = 0x07,
};

// SPI MODE 0: CPOL=0, CPHA=0 (leading edge sample), MSB first, max 5MHz
class MAX11210Sensor : public sensor::Sensor,
                       public PollingComponent,
                       public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW,
                                             spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_4MHZ> {
 public:
  void setup() override;
  void dump_config() override;
  void update() override;
  float get_setup_priority() const override;

  void set_gain(Max11210Gain gain) { this->gain_ = gain; }
  void set_rate(Max11210Rate rate) { this->rate_ = rate; }
  void set_line_frequency_50hz(bool line_50hz) { this->line_50hz_ = line_50hz; }
  void set_reference_voltage(float vref) { this->reference_voltage_ = vref; }
  void set_bipolar(bool bipolar) { this->bipolar_ = bipolar; }
  void set_enable_sig_buf(bool enable) { this->sig_buf_ = enable; }
  void set_enable_ref_buf(bool enable) { this->ref_buf_ = enable; }
  void set_self_calibrate(bool cal) { this->self_calibrate_ = cal; }

 protected:
  // SPI command/register helpers
  void send_command_(uint8_t cmd);
  uint8_t read_register8_(uint8_t reg);
  void write_register8_(uint8_t reg, uint8_t value);
  int32_t read_register24_(uint8_t reg);

  void read_data_();

  Max11210Gain gain_{MAX11210_GAIN_1};
  Max11210Rate rate_{MAX11210_RATE_10SPS};
  bool line_50hz_{true};
  float reference_voltage_{2.5f};
  bool bipolar_{true};
  bool sig_buf_{false};
  bool ref_buf_{false};
  bool self_calibrate_{true};
};

}  // namespace max11210
}  // namespace esphome
