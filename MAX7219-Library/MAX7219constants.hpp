// ==========================================================================
//
// Author    : Stijn van Wijk
// File      : MAX7219constants.hpp
// Part of   : C++ MAX7219 library
// Copyright : stijn.vanwijk@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef MAX7219CONSTANTS_HPP
#define MAX7219CONSTANTS_HPP

/// @file

/// \brief
/// MAX7219 register address
/// \details
/// This enum class contains the MAX7219 register addresses.
/// This enum class is used in the MAX7219 library.
enum class MAX7219_register {
  no_op = 0x00,
  row7,
  row6,
  row5,
  row4,
  row3,
  row2,
  row1,
  row0,
  decode_mode,
  intensity,
  scan_limit,
  shutdown,
  display_test = 0x0F
};

/// \brief
/// MAX7219 commands
/// \details
/// This enum class contains some of the basic MAX7219 commands.
/// This enum class is used in the MAX7219 library.
enum class MAX7219_commands {
  display_normal = 0x00,
  display_test = 0x01,
  decode_none = 0x00,
  shutdown_normal = 0x01,
  scan_limit_max = 0x07,
  intensity_base = 0x05,
  no_op = 0x00
};

#endif