// ==========================================================================
//
// Author    : Stijn van Wijk
// File      : MPU6050constants.hpp
// Part of   : C++ MPU6050 library
// Copyright : stijn.vanwijk@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef MPU6050CONSTANTS_HPP
#define MPU6050CONSTANTS_HPP

/// @file

/// \brief
/// MPU6050 register address
/// \details
/// This enum class contains some of the MPU6050 register addresses.
/// This enum class is used in the MPU6050 library.
enum class MPU6050_register {
  power = 0x6B,
  who_am_i = 0x75,
  gyro_config = 0x1B,
  acc_config,
  acc_x1 = 0x3B,
  acc_x2,
  acc_y1,
  acc_y2,
  acc_z1,
  acc_z2,
  temp1 = 0x41,
  temp2,
  gyro_x1 = 0x43,
  gyro_x2,
  gyro_y1,
  gyro_y2,
  gyro_z1,
  gyro_z2,
};

/// \brief
/// MPU6050 commands
/// \details
/// This enum class contains some of the basic MPU6050 commands.
/// This enum class is used in the MPU6050 library.
enum class MPU6050_commands {
  gyro_250 = 0x00,
  gyro_500 = 0x08,
  gyro_1000 = 0x10,
  gyro_2000 = 0x18,
  acc_2 = 0x00,
  acc_4 = 0x08,
  acc_8 = 0x10,
  acc_16 = 0x18
};

/// \brief
/// MPU6050 range accelerometer
/// \details
/// This enum class contains the possible range settings of the accelerometer.
/// This enum class is used in the MPU6050 library.
enum class acc_full_range { range_2g = 0, range_4g, range_8g, range_16g };

/// \brief
/// MPU6050 range gyroscope
/// \details
/// This enum class contains the possible range settings of the gyroscope.
/// This enum class is used in the MPU6050 library.
enum class gyro_full_range { range_250 = 0, range_500, range_1000, range_2000 };
#endif