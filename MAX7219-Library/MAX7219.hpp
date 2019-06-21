#ifndef MAX7219_hpp
#define MAX7219_hpp

#include "MAX7219constants.hpp"
#include "hwlib.hpp"

using hwlib::color;
using hwlib::cout;
using hwlib::endl;
using hwlib::pin_out;
using hwlib::pin_out_dummy;
using hwlib::wait_ms;
using hwlib::wait_ns;
using hwlib::window;
using hwlib::xy;
using std::array;

class MAX7219 : public window {
 private:
  pin_out& clk;
  pin_out& din;
  pin_out& load;

  unsigned int daisychain_length;
  unsigned int daisychain_position;
  uint64_t write_buffer = 0;
  array<MAX7219_register, 8> rows = {MAX7219_register::row0, MAX7219_register::row1, MAX7219_register::row2,
                                     MAX7219_register::row3, MAX7219_register::row4, MAX7219_register::row5,
                                     MAX7219_register::row6, MAX7219_register::row7};
  // =============== Non-essential functions =======================
  void debugWriteBuffer();
  void debugPrintData(uint16_t to_print);
  // =============== End non-essential functions ===================

  uint16_t createDataBytes(const MAX7219_register& reg, uint8_t right_side);
  void write_implementation(xy pos, color col) override;
  uint64_t bigShiftLeft(const uint64_t& start_value, int shift_number);
  uint64_t bigShiftRight(const uint64_t& start_value, int shift_number);
  void sendData(const MAX7219_register& reg, uint8_t command, bool auto_load = true);
  void sendData(const MAX7219_register& reg, const MAX7219_commands& command, bool auto_load = true);

 public:
  MAX7219(xy size, pin_out& clk_pin, pin_out& din_pin, pin_out& load_pin, unsigned int dc_number = 1, unsigned int dc_pos = 1);
  void initialize(int set_length = 1);
  void clear() override;
  void flush() override;
};

#endif