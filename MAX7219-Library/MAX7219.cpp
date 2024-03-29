// ==========================================================================
//
// Author    : Stijn van Wijk
// File      : MAX7219.cpp
// Part of   : C++ MAX7219 library
// Copyright : stijn.vanwijk@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "MAX7219.hpp"

uint64_t MAX7219::bigShiftLeft(const uint64_t& start_value, int n) {
  uint64_t ret_value = start_value;
  while (n > 16) {
    ret_value = ret_value << 16;
    n -= 16;
  }
  ret_value = ret_value << n;
  return ret_value;
}

uint64_t MAX7219::bigShiftRight(const uint64_t& start_value, int n) {
  uint64_t ret_value = start_value;
  while (n > 16) {
    ret_value = ret_value >> 16;
    n -= 16;
  }
  ret_value = ret_value >> n;
  return ret_value;
}

uint16_t MAX7219::createDataBytes(const MAX7219_register& reg, uint8_t right_side) {
  uint8_t left_side = static_cast<uint8_t>(reg);
  uint16_t ret_value = left_side;
  ret_value = ret_value << 8;
  ret_value |= right_side;
  return ret_value;
}

void MAX7219::sendData(const MAX7219_register& reg, uint8_t command, bool auto_load) {
  uint16_t data = createDataBytes(reg, command);
  int half_clk_cycle = 50;

  load.write(0);
  load.flush();
  for (int_fast8_t shift = 15; shift >= 0; shift--) {
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
  if (auto_load) {
    load.write(1);
    load.flush();
  }
}

void MAX7219::sendData(const MAX7219_register& reg, const MAX7219_commands& command, bool auto_load) {
  uint8_t cmd_uint = static_cast<uint8_t>(command);
  sendData(reg, cmd_uint, auto_load);
}

void MAX7219::sendDataRepeated(const MAX7219_register& reg, const MAX7219_commands& command, int repeats) {
  for (int i = 0; i < repeats; i++) {
    sendData(reg, command, false);
  }
  load.write(1);
  load.flush();
}

void MAX7219::write_implementation(xy pos, color col) {
  int shifts = pos.x + (pos.y * 8);
  write_buffer = write_buffer | bigShiftLeft(1, shifts);
}

void MAX7219::initialize() {
  sendDataRepeated(MAX7219_register::display_test, MAX7219_commands::display_normal, daisychain_length);
  sendDataRepeated(MAX7219_register::shutdown, MAX7219_commands::shutdown_normal, daisychain_length);
  sendDataRepeated(MAX7219_register::decode_mode, MAX7219_commands::decode_none, daisychain_length);
  sendDataRepeated(MAX7219_register::scan_limit, MAX7219_commands::scan_limit_max, daisychain_length);
  sendDataRepeated(MAX7219_register::intensity, MAX7219_commands::intensity_base, daisychain_length);
}

void MAX7219::clear() {
  write_buffer = 0;
  prev_write_buffer = ~0;
  flush();
}

void MAX7219::flush() {
  unsigned int no_ops = daisychain_length - 1;
  unsigned int pre_ops = daisychain_length - daisychain_position;
  unsigned int post_ops = no_ops - pre_ops;

  for (int i = 0; i < 8; i++) {
    MAX7219_register reg = rows[i];
    uint8_t prev_command = (bigShiftRight(prev_write_buffer, 8 * i) & 0xFF);
    uint8_t command = (bigShiftRight(write_buffer, 8 * i) & 0xFF);
    if (prev_command != command) {
      for (unsigned int pre = 0; pre < pre_ops; pre++) {
        sendData(MAX7219_register::no_op, MAX7219_commands::no_op, false);
      }
      sendData(reg, command, false);
      for (unsigned int post = 0; post < post_ops; post++) {
        sendData(MAX7219_register::no_op, MAX7219_commands::no_op, false);
      }
      load.write(1);
      load.flush();
    }
  }
  prev_write_buffer = write_buffer;
  write_buffer = 0;
}