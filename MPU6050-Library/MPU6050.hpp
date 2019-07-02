#ifndef MPU6050_HPP
#define MPU6050_HPP

#include "MPU6050constants.hpp"
#include "hwlib.hpp"
#include "math.h"

using hwlib::cout;
using hwlib::endl;
using hwlib::i2c_bus;
using hwlib::now_us;

/// @file

/// \brief
/// Datastruct XYZ values
/// \details
/// This struct contains x,y and z what are int16_t.\n
/// Used in the MPU6050 library.\n
struct xyzData {
  int16_t x;
  int16_t y;
  int16_t z;
};

/// \brief
/// Datastruct Error values MPU6050
/// \details
/// This scruct contains the possible error values of the MPU6050.\n
/// Used in the MPU6050 library.\n
/// The standard values of all errors is 0.\n
struct errorData {
  double acc_x = 0;
  double acc_y = 0;
  double gyro_x = 0;
  double gyro_y = 0;
  double gyro_z = 0;
};

/// \brief
/// MPU6050 interface library
/// \details
/// This is a library for the MPU6050.\n
/// It implements an interface for the user.\n
/// The communication protocol is I2C.\n
/// The appropriate constructor is given.\n
class MPU6050 {
 private:
  i2c_bus& bus;
  uint8_t address;
  uint8_t read_buffer;
  double lsb_acc;
  double lsb_gyro;
  errorData errors;
  float pi = 3.141593;

  /// \brief
  /// Read register
  /// \details
  /// This function reads the given register from the MPU6050.\n
  /// This function expects a MPU6050_register, this is an address.\n
  /// The byte that is read, is saved in the read_buffer.\n
  void readRegister(const MPU6050_register& reg);

  /// \brief
  /// Write data to register
  /// \details
  /// This function writes the given data to the register on the MPU6050.\n
  /// This function expects a MPU6050_register and a data byte.\n
  void writeRegister(const MPU6050_register& reg, uint8_t data);

  /// \brief
  /// Write command to register
  /// \details
  /// This function writes the given MPU6050_command to the register on the MPU6050.\n
  /// This function expects a MPU6050_register and en MPU6050_command.\n
  void writeRegister(const MPU6050_register& reg, const MPU6050_commands& data);

  /// \brief
  /// Read register return
  /// \details
  /// This function reads the given register from the MPU6050.\n
  /// This function expects a MPU6050_register, this is an address.\n
  /// The byte that is read, is returned by the function.\n
  uint8_t readRegisterReturn(const MPU6050_register& reg);

  /// \brief
  /// Read multiple registers
  /// \details
  /// This function reads two registers and combines the two bytes to a uint16_t.\n
  /// This funcion expects two MPU6050_registers. The first register given is shifted left by 8.\n
  uint16_t combineRegisters(const MPU6050_register& reg_l, const MPU6050_register& reg_r);

 public:
  /// \brief
  /// Constructor MPU6050
  /// \details
  /// This constructor creates a MPU6050 object.\n
  /// You are obligated to give a i2c_bus.\n
  /// When the AD0 is connected to VCC, the address should be 0x69.\n
  /// Call example: auto mpu = MPU6050(bus_bit_banged);
  MPU6050(i2c_bus& bus, uint8_t address = 0x68) : bus(bus), address(address), read_buffer(0) {
    writeRegister(MPU6050_register::power, 0x00);
    setFullRange();
  }

  /// \brief
  /// Print WhoAmI register
  /// \details
  /// This function prints the decimal value that is in the WhoAmI register.\n
  /// The decimal value should be the same as the address.\n
  /// This function can be used to check if the MPU6050 is working correctly.\n
  /// Call example: mpu.whoAmI(); (mpu is the mpu6050 object)
  void whoAmI();

  /// \brief
  /// Calibrate MPU6050
  /// \details
  /// This function calculates the error values of the different sensors.\n
  /// It is optional to call this function.\n
  /// It is done by taking multiple measurements, and taking the avarage of those measurements.\n
  /// For the calbration to work properly, you must be sure that the MPU6050 is level.\n
  /// Call example: mpu.calibrate(400);
  void calibrate(unsigned int sample_rate = 200);

  /// \brief
  /// Set range accelerometer and gyroscope
  /// \details
  /// This function makes you able to set the range of the accelerometer and gyroscope.\n
  /// The range is to amount of change the sensor can measure.\n
  /// If range is bigger, the precision is less.\n
  /// It expects acc_full_range and a gyro_full_range.\n
  /// Call example: mpu.setFullRange(acc_full_range::range_8g, gyro_full_range::range_1000);
  void setFullRange(acc_full_range range_acc = acc_full_range::range_2g,
                    gyro_full_range range_gyro = gyro_full_range::range_250);

  /// \brief
  /// Get raw accelerometer X-axis
  /// \details
  /// This function returns the 16-bits that are found in the two corresponding registers.\n
  /// It returns a int16_t, this is rawdata.\n
  /// Call example: int16_t raw_acc_x = mpu.getAccX();
  int16_t getAccX();

  /// \brief
  /// Get raw accelerometer Y-axis
  /// \details
  /// This function returns the 16-bits that are found in the two corresponding registers.\n
  /// It returns a int16_t, this is rawdata.\n
  /// Call example: int16_t raw_acc_y = mpu.getAccY();
  int16_t getAccY();

  /// \brief
  /// Get raw accelerometer Z-axis
  /// \details
  /// This function returns the 16-bits that are found in the two corresponding registers.\n
  /// It returns a int16_t, this is rawdata.\n
  /// Call example: int16_t raw_acc_z = mpu.getAccZ();
  int16_t getAccZ();

  /// \brief
  /// Get rawdata accelerometer XYZ-axis
  /// \details
  /// This function returns a xyzData struct.\n
  /// This struct contains the rawData of the X, Y and Z-axis of the accelerometer.\n
  /// Call example: auto raw_acc_all = mpu.getAccAll();
  xyzData getAccAll();

  /// \brief
  /// Get raw gyroscope X-axis
  /// \details
  /// This function returns the 16-bits that are found in the two corresponding registers.\n
  /// It returns a int16_t, this is rawdata.\n
  /// Call example: int16_t raw_gyro_x = mpu.getGyroX();
  int16_t getGyroX();

  /// \brief
  /// Get raw gyroscope Y-axis
  /// \details
  /// This function returns the 16-bits that are found in the two corresponding registers.\n
  /// It returns a int16_t, this is rawdata.\n
  /// Call example: int16_t raw_gyro_y = mpu.getGyroY();
  int16_t getGyroY();

  /// \brief
  /// Get raw gyroscope Z-axis
  /// \details
  /// This function returns the 16-bits that are found in the two corresponding registers.\n
  /// It returns a int16_t, this is rawdata.\n
  /// Call example: int16_t raw_gyro_z = mpu.getGyroZ();
  int16_t getGyroZ();

  /// \brief
  /// Get rawdata gyroscope XYZ-axis
  /// \details
  /// This function returns a xyzData struct.\n
  /// This struct contains the rawData of the X, Y and Z-axis of the gyroscope.\n
  /// Call example: auto raw_gyro_all = mpu.getGyroAll();
  xyzData getGyroAll();

  /// \brief
  /// Get angle X-axis
  /// \details
  /// This function returns the angle of the MPU6050 in the X-axis.\n
  /// This is a value between -90 and 90 degrees.\n
  /// The angle is calculated on the data from the accelerometer.\n
  /// Call example: int angle_x = mpu.getAngleX();
  int getAngleX();

  /// \brief
  /// Get angle Y-axis
  /// \details
  /// This function returns the angle of the MPU6050 in the Y-axis.\n
  /// This is a value between -90 and 90 degrees.\n
  /// The angle is calculated on the data from the accelerometer.\n
  /// Call example: int angle_y = mpu.getAngleY();
  int getAngleY();

  /// \brief
  /// Get temperature
  /// \details
  /// This function returns the temperature of the current MPU6050 surroundings.\n
  /// Call example: int temp = mpu.getTemprature();
  int getTemperature();
};

#endif