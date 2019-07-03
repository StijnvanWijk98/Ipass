// ==========================================================================
//
// Author    : Stijn van Wijk
// File      : testFunctions.cpp
// Part of   : C++ MPU6050 library
// Copyright : stijn.vanwijk@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "testFunctions.hpp"

void testAngleX(MPU6050& mpu) {
  for (int i = 0; i < 10; i++) {
    int angle_x = mpu.getAngleX();
    cout << "angle_x: " << angle_x << "\n";
    wait_ms(1000);
  }
}

void testAngleY(MPU6050& mpu) {
  for (int i = 0; i < 10; i++) {
    int angle_y = mpu.getAngleY();
    cout << "angle_y: " << angle_y << "\n";
    wait_ms(1000);
  }
}

void testGyroX(MPU6050& mpu) {
  for (int i = 0; i < 10; i++) {
    int gyroscope_x = mpu.getGyroX();
    cout << "gyroscope_x: " << gyroscope_x << "\n";
    wait_ms(1000);
  }
}

void testGyroY(MPU6050& mpu) {
  for (int i = 0; i < 10; i++) {
    int gyroscope_y = mpu.getGyroX();
    cout << "gyroscope_y: " << gyroscope_y << "\n";
    wait_ms(1000);
  }
}

void testGyroZ(MPU6050& mpu) {
  for (int i = 0; i < 10; i++) {
    int gyroscope_z = mpu.getGyroX();
    cout << "gyroscope_z: " << gyroscope_z << "\n";
    wait_ms(1000);
  }
}