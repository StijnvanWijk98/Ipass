#include "MAX7219.hpp"

int main() {
  wait_ms(500);
  namespace target = hwlib::target;
  auto clk = target::pin_out(target::pins::d10);
  auto din = target::pin_out(target::pins::d8);
  auto load = target::pin_out(target::pins::d9);

  MAX7219 matrix = MAX7219(clk, din, load);
  matrix.initialize();
  matrix.sendData(MAX7219_register::row0, 0x01);
  matrix.sendData(MAX7219_register::row1, 0x02);
  matrix.sendData(MAX7219_register::row2, 0x04);
  matrix.sendData(MAX7219_register::row3, 0x08);
  matrix.sendData(MAX7219_register::row4, 0x10);
  matrix.sendData(MAX7219_register::row5, 0x20);
  matrix.sendData(MAX7219_register::row6, 0x40);
  matrix.sendData(MAX7219_register::row7, 0x80);

  return 0;
}
