#ifndef MPU6050_HPP
#define MPU6050_HPP

#include "MPU6050constants.hpp"
#include "hwlib.hpp"
#include "math.h"

using hwlib::cout;
using hwlib::endl;
using hwlib::i2c_bus;
using hwlib::now_us;

namespace mpu6050 {
  struct accData {
    int16_t acc_x;
    int16_t acc_y;
    int16_t acc_z;
  };

  struct gyroData {
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
  };

  class MPU6050 {
   private:
    i2c_bus& bus;
    uint8_t address;
    uint8_t read_buffer;
    uint64_t time_cur;
    double lsb_acc;
    double lsb_gyro;

   public:
    // ========================= Non-essential functions =========================
    void printReadBuffer();

    // ========================= End Non-essential functions =====================
    MPU6050(i2c_bus& bus, uint8_t address = 0x68);
    void calibrate();
    void setFullRange(acc_full_range range_acc = acc_full_range::range_2g,
                      gyro_full_range range_gyro = gyro_full_range::range_250);

    void readRegister(const registers& reg);
    void writeRegister(const registers& reg, uint8_t data);
    void writeRegister(const registers& reg, const commands& pre_data);
    uint16_t combineRegisters(const registers& reg_l, const registers& reg_r);
    uint8_t readRegisterReturn(const registers& reg);

    int16_t getAccX();
    int16_t getAccY();
    int16_t getAccZ();
    accData getAccAll();

    int16_t getGyroX();
    int16_t getGyroY();
    int16_t getGyroZ();
    gyroData getGyroAll();

    int getAngleX();
    int getAngleY();
  };
}  // namespace mpu6050

#endif