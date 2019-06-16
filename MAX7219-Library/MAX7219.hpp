#include "constants.hpp"
#include "hwlib.hpp"

using hwlib::cout;
using hwlib::endl;
using hwlib::pin_out;
using hwlib::pin_out_dummy;
using hwlib::wait_ms;
using hwlib::wait_ns;

class MAX7219 {
 private:
  pin_out& clk;
  pin_out& din;
  pin_out& load;
  uint16_t createDataBytes(const MAX7219_register& reg, uint8_t right_side);
  void debugPrintData(uint16_t to_print);

  int amount_matricis;

 public:
  MAX7219(pin_out& clk_pin, pin_out& din_pin, pin_out& load_pin, int amount_matricis);
  void initialize();
  void sendData(const MAX7219_register& reg, uint8_t command);
  void clear();
};