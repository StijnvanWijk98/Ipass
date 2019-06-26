#include "MPU6050.hpp"

namespace mpu6050 {
  // ========================= Non-essential functions =========================
  void MPU6050::printReadBuffer() { cout << "read_buffer = " << read_buffer << endl; }

  void MPU6050::whoAmI(){
    readRegister(registers::who_am_i);
    cout << "who am i: " << read_buffer << endl;
  }
  // ========================= End Non-essential functions =====================

  MPU6050::MPU6050(i2c_bus& bus, uint8_t address) : bus(bus), address(address), read_buffer(0) {
    time_cur = now_us();
    writeRegister(registers::power, 0x00);
    setFullRange();
  }

  void MPU6050::calibrate(unsigned int sample_rate) { // Threshhold feature toevoegen zodat je zeker weet dat het apperaat stil ligt
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

  uint16_t MPU6050::combineRegisters(const registers& reg_l, const registers& reg_r) {
    uint8_t tmp = readRegisterReturn(reg_l);
    uint8_t tmp2 = readRegisterReturn(reg_r);
    uint16_t ret_value = tmp << 8;
    ret_value = ret_value | tmp2;
    return ret_value;
  }

  void MPU6050::readRegister(const registers& reg) {
    uint8_t reg_address = static_cast<uint8_t>(reg);
    bus.write(address).write(reg_address);
    bus.read(address).read(read_buffer);
  }
  uint8_t MPU6050::readRegisterReturn(const registers& reg) {
    readRegister(reg);
    return read_buffer;
  }
  void MPU6050::writeRegister(const registers& reg, uint8_t data) {
    uint8_t reg_address = static_cast<uint8_t>(reg);
    uint8_t data_send[2] = {reg_address, data};
    bus.write(address).write(data_send, 2);
  }
  void MPU6050::writeRegister(const registers& reg, const commands& data) {
    uint8_t to_send = static_cast<uint8_t>(data);
    writeRegister(reg, to_send);
  }

  void MPU6050::setFullRange(acc_full_range range_acc, gyro_full_range range_gyro) {
    switch (range_acc) {
      case acc_full_range::range_2g:
        writeRegister(registers::acc_config, commands::acc_2);
        lsb_acc = 16384.0;
        break;
      case acc_full_range::range_4g:
        writeRegister(registers::acc_config, commands::acc_4);
        lsb_acc = 8192.0;
        break;
      case acc_full_range::range_8g:
        writeRegister(registers::acc_config, commands::acc_8);
        lsb_acc = 4096.0;
        break;
      case acc_full_range::range_16g:
        writeRegister(registers::acc_config, commands::acc_16);
        lsb_acc = 2048.0;
        break;
    }

    switch (range_gyro) {
      case gyro_full_range::range_250:
        writeRegister(registers::gyro_config, commands::gyro_250);
        lsb_gyro = 131.0;
        break;
      case gyro_full_range::range_500:
        writeRegister(registers::gyro_config, commands::gyro_500);
        lsb_gyro = 65.5;
        break;
      case gyro_full_range::range_1000:
        writeRegister(registers::gyro_config, commands::gyro_1000);
        lsb_gyro = 32.8;
        break;
      case gyro_full_range::range_2000:
        writeRegister(registers::gyro_config, commands::gyro_2000);
        lsb_gyro = 16.4;
        break;
    }
  }

  int16_t MPU6050::getAccX() { return combineRegisters(registers::acc_x1, registers::acc_x2); }
  int16_t MPU6050::getAccY() { return combineRegisters(registers::acc_y1, registers::acc_y2); }
  int16_t MPU6050::getAccZ() { return combineRegisters(registers::acc_z1, registers::acc_z2); }

  accData MPU6050::getAccAll() {
    int16_t acc_x = getAccX();
    int16_t acc_y = getAccY();
    int16_t acc_z = getAccZ();
    accData ret_struct = {acc_x, acc_y, acc_z};
    return ret_struct;
  }

  int16_t MPU6050::getGyroX() { return combineRegisters(registers::gyro_x1, registers::gyro_x2); }
  int16_t MPU6050::getGyroY() { return combineRegisters(registers::gyro_y1, registers::gyro_y2); }
  int16_t MPU6050::getGyroZ() { return combineRegisters(registers::gyro_z1, registers::gyro_z2); }

  gyroData MPU6050::getGyroAll() {
    int16_t gyro_x = getGyroX();
    int16_t gyro_y = getGyroY();
    int16_t gyro_z = getGyroZ();
    gyroData ret_struct = {gyro_x, gyro_y, gyro_z};
    return ret_struct;
  }

  int MPU6050::getAngleX() {
    float pi = 3.141593;
    int16_t x = getAccX();
    int16_t y = getAccY();
    int16_t z = getAccZ();
    return (atan(y / sqrt((x * x) + (z * z))) * 180 / pi) - errors.acc_x;
  }

  int MPU6050::getAngleY() {
    float pi = 3.141593;
    int16_t x = getAccX();
    int16_t y = getAccY();
    int16_t z = getAccZ();
    return (atan(-1 * x / sqrt((y * y) + (z * z))) * 180 / pi) - errors.acc_y;
  }

}  // namespace mpu6050
