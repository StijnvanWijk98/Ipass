#include "MAX7219.hpp"

int main() {
  wait_ms(500);
  namespace target = hwlib::target;
  auto clk = target::pin_out(target::pins::d10);
  auto din = target::pin_out(target::pins::d8);
  auto load = target::pin_out(target::pins::d9);

  MAX7219 matrix = MAX7219(clk, din, load, 2);
  matrix.initialize();
  // matrix.sendData(MAX7219_register::column0, 0x0F);
  // matrix.sendData(MAX7219_register::column1, 0xF0);
  matrix.sendDataRepeated(MAX7219_register::column0, 0x0F, 2);

  return 0;
}
