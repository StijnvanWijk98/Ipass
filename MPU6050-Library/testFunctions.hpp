// ==========================================================================
//
// Author    : Stijn van Wijk
// File      : testFunctions.hpp
// Part of   : C++ MPU6050 library
// Copyright : stijn.vanwijk@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef TESTFUNCTIONS_HPP
#define TESTFUNCTIONS_HPP

#include "MPU6050.hpp"
using hwlib::wait_ms;

void testAngleX(MPU6050& mpu);

void testAngleY(MPU6050& mpu);

void testGyroX(MPU6050& mpu);

void testGyroY(MPU6050& mpu);

void testGyroZ(MPU6050& mpu);

#endif  // TESTFUNCTIONS_HPP