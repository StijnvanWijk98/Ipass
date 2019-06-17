#include "constants.hpp"
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

  uint64_t write_buffer = 0;
  array<MAX7219_register, 8> rows = {MAX7219_register::row0, MAX7219_register::row1, MAX7219_register::row2,
                                     MAX7219_register::row3, MAX7219_register::row4, MAX7219_register::row5,
                                     MAX7219_register::row6, MAX7219_register::row7};

  uint16_t createDataBytes(const MAX7219_register& reg, uint8_t right_side);
  void debugPrintData(uint16_t to_print);
  void write_implementation(xy pos, color col) override;
  uint64_t bigShiftLeft(const uint64_t& start_value, int shift_number);
  uint64_t bigShiftRight(const uint64_t& start_value, int shift_number);

 public:
  MAX7219(xy size, pin_out& clk_pin, pin_out& din_pin, pin_out& load_pin);
  void initialize();
  void sendData(const MAX7219_register& reg, uint8_t command, bool repeated = false);
  void clear();
  void flush() override;
  void debugWriteBuffer();
};