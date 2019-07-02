// ==========================================================================
//
// Author    : Stijn van Wijk
// File      : MPU6050.cpp
// Part of   : C++ MPU6050 library
// Copyright : stijn.vanwijk@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "MPU6050.hpp"

void MPU6050::whoAmI() {
  readRegister(MPU6050_register::who_am_i);
  cout << "who am i: " << read_buffer << endl;
}

void MPU6050::calibrate(
    unsigned int sample_rate) {  // Threshhold feature toevoegen zodat je zeker weet dat het apperaat stil ligt
  cout << "Calibrating, keep sensor still......" << endl;
  double error_acc_x = 0;
  double error_acc_y = 0;
  double error_gyro_x = 0;
  double error_gyro_y = 0;
  double error_gyro_z = 0;

  for (unsigned int i = 0; i < sample_rate; i++) {
    error_acc_x += getAngleX();
    error_acc_y += getAngleY();
    error_gyro_x = getGyroX() / lsb_gyro;
    error_gyro_y = getGyroY() / lsb_gyro;
    error_gyro_z = getGyroZ() / lsb_gyro;
  }
  errors.acc_x = (error_acc_x / sample_rate);
  errors.acc_y = (error_acc_y / sample_rate);
  errors.gyro_x = (error_gyro_x / sample_rate);
  errors.gyro_y = (error_gyro_y / sample_rate);
  errors.gyro_z = (error_gyro_z / sample_rate);
  cout << "Calibrating done" << endl;
}

uint16_t MPU6050::combineRegisters(const MPU6050_register& reg_l, const MPU6050_register& reg_r) {
  uint8_t tmp = readRegisterReturn(reg_l);
  uint8_t tmp2 = readRegisterReturn(reg_r);
  uint16_t ret_value = tmp << 8;
  ret_value = ret_value | tmp2;
  return ret_value;
}

void MPU6050::readRegister(const MPU6050_register& reg) {
  uint8_t reg_address = static_cast<uint8_t>(reg);
  bus.write(address).write(reg_address);
  bus.read(address).read(read_buffer);
}
uint8_t MPU6050::readRegisterReturn(const MPU6050_register& reg) {
  readRegister(reg);
  return read_buffer;
}
void MPU6050::writeRegister(const MPU6050_register& reg, uint8_t data) {
  uint8_t reg_address = static_cast<uint8_t>(reg);
  uint8_t data_send[2] = {reg_address, data};
  bus.write(address).write(data_send, 2);
}
void MPU6050::writeRegister(const MPU6050_register& reg, const MPU6050_commands& data) {
  uint8_t to_send = static_cast<uint8_t>(data);
  writeRegister(reg, to_send);
}

void MPU6050::setFullRange(acc_full_range range_acc, gyro_full_range range_gyro) {
  switch (range_acc) {
    case acc_full_range::range_2g:
      writeRegister(MPU6050_register::acc_config, MPU6050_commands::acc_2);
      lsb_acc = 16384.0;
      break;
    case acc_full_range::range_4g:
      writeRegister(MPU6050_register::acc_config, MPU6050_commands::acc_4);
      lsb_acc = 8192.0;
      break;
    case acc_full_range::range_8g:
      writeRegister(MPU6050_register::acc_config, MPU6050_commands::acc_8);
      lsb_acc = 4096.0;
      break;
    case acc_full_range::range_16g:
      writeRegister(MPU6050_register::acc_config, MPU6050_commands::acc_16);
      lsb_acc = 2048.0;
      break;
  }

  switch (range_gyro) {
    case gyro_full_range::range_250:
      writeRegister(MPU6050_register::gyro_config, MPU6050_commands::gyro_250);
      lsb_gyro = 131.0;
      break;
    case gyro_full_range::range_500:
      writeRegister(MPU6050_register::gyro_config, MPU6050_commands::gyro_500);
      lsb_gyro = 65.5;
      break;
    case gyro_full_range::range_1000:
      writeRegister(MPU6050_register::gyro_config, MPU6050_commands::gyro_1000);
      lsb_gyro = 32.8;
      break;
    case gyro_full_range::range_2000:
      writeRegister(MPU6050_register::gyro_config, MPU6050_commands::gyro_2000);
      lsb_gyro = 16.4;
      break;
  }
}

int16_t MPU6050::getAccX() { return combineRegisters(MPU6050_register::acc_x1, MPU6050_register::acc_x2); }
int16_t MPU6050::getAccY() { return combineRegisters(MPU6050_register::acc_y1, MPU6050_register::acc_y2); }
int16_t MPU6050::getAccZ() { return combineRegisters(MPU6050_register::acc_z1, MPU6050_register::acc_z2); }

xyzData MPU6050::getAccAll() {
  int16_t acc_x = getAccX();
  int16_t acc_y = getAccY();
  int16_t acc_z = getAccZ();
  xyzData ret_struct = {acc_x, acc_y, acc_z};
  return ret_struct;
}

int16_t MPU6050::getGyroX() { return combineRegisters(MPU6050_register::gyro_x1, MPU6050_register::gyro_x2); }
int16_t MPU6050::getGyroY() { return combineRegisters(MPU6050_register::gyro_y1, MPU6050_register::gyro_y2); }
int16_t MPU6050::getGyroZ() { return combineRegisters(MPU6050_register::gyro_z1, MPU6050_register::gyro_z2); }

xyzData MPU6050::getGyroAll() {
  int16_t gyro_x = getGyroX();
  int16_t gyro_y = getGyroY();
  int16_t gyro_z = getGyroZ();
  xyzData ret_struct = {gyro_x, gyro_y, gyro_z};
  return ret_struct;
}

int MPU6050::getAngleX() {
  int16_t x = getAccX();
  int16_t y = getAccY();
  int16_t z = getAccZ();
  return (atan(y / sqrt((x * x) + (z * z))) * 180 / pi) - errors.acc_x;
}

int MPU6050::getAngleY() {
  int16_t x = getAccX();
  int16_t y = getAccY();
  int16_t z = getAccZ();
  return (atan(-1 * x / sqrt((y * y) + (z * z))) * 180 / pi) - errors.acc_y;
}

int MPU6050::getTemperature() {
  int16_t raw_value = combineRegisters(MPU6050_register::temp1, MPU6050_register::temp2);
  return (raw_value / 340 + 36.53);
}