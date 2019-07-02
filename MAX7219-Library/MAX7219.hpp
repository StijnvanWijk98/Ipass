// ==========================================================================
//
// Author    : Stijn van Wijk
// File      : MAX7219.hpp
// Part of   : C++ MAX7219 library
// Copyright : stijn.vanwijk@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

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

/// @file

/// \brief
/// MAX7219 8x8 ledmatrix controller
/// \details
/// This is a library for the MAX7219 ledcontroller.\n
/// It uses three pin_outs to communicate with the MAX7219.\n
/// With the library you are able to daisychain the MAX7219.\n
/// The library implements the MAX7219 as a hwlib window.\n
/// The interface that the user uses is a hwlib window.\n
/// The appropriate constructor is given.
class MAX7219 : public window {
 private:
  pin_out& clk;
  pin_out& din;
  pin_out& load;

  unsigned int daisychain_length;
  unsigned int daisychain_position;

  uint64_t write_buffer = 0;
  uint64_t prev_write_buffer = 0;
  array<MAX7219_register, 8> rows = {MAX7219_register::row0, MAX7219_register::row1, MAX7219_register::row2,
                                     MAX7219_register::row3, MAX7219_register::row4, MAX7219_register::row5,
                                     MAX7219_register::row6, MAX7219_register::row7};

  /// \brief
  /// Shift uint64_t n*left
  /// \details
  /// This function returns the given start_value (uint64_t) n times to the left.\n
  /// It returns an uint64_t.\n
  /// The functions solves the problem of getting undefined behaviour when shifting above 31.
  uint64_t bigShiftLeft(const uint64_t& start_value, int n);

  /// \brief
  /// Shift uint64_t n*right
  /// \details
  /// This function returns the given start_value (uint64_t) n times to the right.\n
  /// It returns an uint64_t.\n
  /// The functions solves the problem of getting undefined behaviour when shifting above 31.
  uint64_t bigShiftRight(const uint64_t& start_value, int n);

  /// \brief
  /// Create data send bytes
  /// \details
  /// This function creates the uint16_t that are sended to the MAX7219.\n
  /// It merges a MAX7219_register address and an uint8_t to form a uint16_t.\n
  /// The function returns an uint16_t.
  uint16_t createDataBytes(const MAX7219_register& reg, uint8_t right_side);

  /// \brief
  /// Send data to MAX7219
  /// \details
  /// This function sends the given MAX7219_register address and uint8_t to the MAX7219.\n
  /// When the MAX7219 is daisychained auto_load needs to be false.
  void sendData(const MAX7219_register& reg, uint8_t command, bool auto_load = true);

  /// \brief
  /// Send data to MAX7219
  /// \details
  /// This function sends the given MAX7219_register address and MAX7219_command to the MAX7219.\n
  /// When the MAX7219 is daisychained auto_load needs to be false.
  void sendData(const MAX7219_register& reg, const MAX7219_commands& command, bool auto_load = true);

  /// \brief
  /// Send data to multiple MAX7219
  /// \details
  /// This function sends the given MAX7219_register address and MAX7219_command to multiple MAX7219.\n
  /// This function is intented for use in a daisychain.\n
  /// It sends the data to repeats number of MAX7219.
  void sendDataRepeated(const MAX7219_register& reg, const MAX7219_commands& command, int repeats);

  /// \brief
  /// write a pixel - implementation
  /// \details
  /// This function puts the pixel in a buffer.\n
  /// The pixel is a xy location on the window.
  void write_implementation(xy pos, color col) override;

 public:
  /// \brief
  /// Constructor MAX7219
  /// \details
  /// The constructor creates a MAX7219 object.\n
  /// You are obligated to give the windowsize and the three pins, the advised windowsize is 8x8.\n
  /// If the MAX7219 is used in a daisychain you are obligated to give the daisychain length and position.\n
  /// dc_pos should NEVER be greater than dc_length. dc stands for daisychain.\n
  /// Call example: auto window_matrix = MAX7219(xy(8,8), clk, din, load, 3, 2)
  MAX7219(xy size, pin_out& clk_pin, pin_out& din_pin, pin_out& load_pin, unsigned int dc_length = 1,
          unsigned int dc_pos = 1)
      : window(size),
        clk(clk_pin),
        din(din_pin),
        load(load_pin),
        daisychain_length(dc_length),
        daisychain_position(dc_pos) {}

  /// \brief
  /// Initialize the MAX7219
  /// \details
  /// This function initializes and powers up the MAX7219.\n
  /// When the MAX7219 is in a daisychain only call function on one of the screens in the daisychain.\n
  /// Call example: window_matrix.initialize();
  void initialize();

  /// \brief
  /// Clear the window
  /// \details
  /// This function clears the window.\n
  /// It also empties out the buffer.\n
  /// Add start-up call the clear function on the screen to make sure it is empty.\n
  /// Call example: window_matrix.clear();
  void clear() override;

  /// \brief
  /// Flush buffer on window
  /// \details
  /// This function flushes the buffer to the window.\n
  /// After flusing the buffer is cleared.\n
  /// Call example: window_matrix.flush();
  void flush() override;
};

#endif