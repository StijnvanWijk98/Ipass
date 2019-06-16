#include "MAX7219.hpp"

MAX7219::MAX7219(pin_out& clk_pin, pin_out& din_pin, pin_out& load_pin) : clk(clk_pin), din(din_pin), load(load_pin) {}

uint16_t MAX7219::createDataBytes(const MAX7219_register& reg, uint8_t right_side) {
  uint8_t left_side = static_cast<uint8_t>(reg);
  uint16_t ret_value = left_side;
  ret_value = ret_value << 8;
  ret_value |= right_side;
  return ret_value;
}

void MAX7219::debugPrintData(uint16_t to_print) {
  for (int i = 15; i >= 0; i--) {
    cout << "i:" << i << '-' << (to_print & (1 << i)) << endl;
  }
}

void MAX7219::sendData(const MAX7219_register& reg, uint8_t command) {
  uint16_t data = createDataBytes(reg, command);
  int half_clk_cycle = 100;

  load.write(0);
  load.flush();
  wait_ns(50);
  for (int_fast8_t shift = 16; shift >= 0; shift--) {
    uint16_t write_data = data & (1 << shift);
    din.write(write_data);
    din.flush();
    hwlib::wait_ns(half_clk_cycle);
    clk.write(1);
    clk.flush();
    hwlib::wait_ns(half_clk_cycle);
    clk.write(0);
    clk.flush();
  }
  load.write(1);
  load.flush();
}

void MAX7219::initialize() {
  sendData(MAX7219_register::display_test, 0x00);
  sendData(MAX7219_register::shutdown, 0x01);
  sendData(MAX7219_register::decode_mode, 0x00);
  sendData(MAX7219_register::scan_limit, 0x07);
  sendData(MAX7219_register::intensity, 0x05);
  clear();
}

void MAX7219::clear() {
  sendData(MAX7219_register::row0, 0x00);
  sendData(MAX7219_register::row1, 0x00);
  sendData(MAX7219_register::row2, 0x00);
  sendData(MAX7219_register::row3, 0x00);
  sendData(MAX7219_register::row4, 0x00);
  sendData(MAX7219_register::row5, 0x00);
  sendData(MAX7219_register::row6, 0x00);
  sendData(MAX7219_register::row7, 0x00);
}