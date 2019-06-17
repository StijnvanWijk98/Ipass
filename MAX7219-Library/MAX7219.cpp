#include "MAX7219.hpp"

MAX7219::MAX7219(xy size, pin_out& clk_pin, pin_out& din_pin, pin_out& load_pin)
    : window(size), clk(clk_pin), din(din_pin), load(load_pin) {}

/*
 * This function returns the start value shifted to the left by shift_number.
 * Use this function when you want to shift above 30.
 */
uint64_t MAX7219::bigShiftLeft(const uint64_t& start_value, int shift_number) {
  uint64_t ret_value = start_value;
  while (shift_number > 16) {
    ret_value = ret_value << 16;
    shift_number -= 16;
  }
  ret_value = ret_value << shift_number;
  return ret_value;
}

/*
 * This function returns the start value shifted to the right by shift_number.
 * Use this function when you want to shift above 30.
 */
uint64_t MAX7219::bigShiftRight(const uint64_t& start_value, int shift_number) {
  uint64_t ret_value = start_value;
  while (shift_number > 16) {
    ret_value = ret_value >> 16;
    shift_number -= 16;
  }
  ret_value = ret_value >> shift_number;
  return ret_value;
}

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

/*
 * This prints out the writebuffer in 0, when a row is only 0 dont write it.
 */
void MAX7219::debugWriteBuffer() {
  cout << "Writebuffer:" << endl;
  for (int i = 0; i < 8; i++) {
    uint64_t res_shift = bigShiftRight(write_buffer, i * 8);
    uint8_t onerow = (res_shift & 0xFF);
    if (onerow == 0) continue;
    cout << "i:" << i << " row:" << onerow << endl;
    for (int j = 0; j < 8; j++) {
      bool bit = onerow & (1 << j);
      cout << bit;
    }
    cout << endl;
  }
}

void MAX7219::sendData(const MAX7219_register& reg, uint8_t command, bool repeated) {
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
  if (!repeated) {
    load.write(1);
    load.flush();
  }
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
  write_buffer = 0;
  flush();
}

void MAX7219::write_implementation(xy pos, color col) {
  int shifts = pos.x + (pos.y * 8);
  write_buffer = write_buffer | bigShiftLeft(1, shifts);
}

void MAX7219::flush() {
  for (int i = 0; i < 8; i++) {
    MAX7219_register reg = rows[i];
    uint8_t command = (bigShiftRight(write_buffer, 8 * i) & 0xFF);
    sendData(reg, command);
  }
  write_buffer = 0;
}