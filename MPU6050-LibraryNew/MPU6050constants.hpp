#ifndef MPU6050CONSTANTS_HPP
#define MPU6050CONSTANTS_HPP

namespace mpu6050 {

  enum class registers {
    power = 0x6B,
    who_am_i = 0x75,
    gyro_config = 0x1B,
    acc_config,
    acc_x1 = 0x3B,
    acc_x2 = 0x3C,
    acc_y1,
    acc_y2,
    acc_z1,
    acc_z2,
    temp1 = 0x41,
    temp2 = 0x42,
    gyro_x1 = 0x43,
    gyro_x2 = 0x44,
    gyro_y1 = 0x45,
    gyro_y2 = 0x46,
    gyro_z1 = 0x47,
    gyro_z2 = 0x48,
  };

  enum class commands {
    gyro_250 = 0x00,
    gyro_500 = 0x08,
    gyro_1000 = 0x10,
    gyro_2000 = 0x18,
    acc_2 = 0x00,
    acc_4 = 0x08,
    acc_8 = 0x10,
    acc_16 = 0x18
  };

  enum class acc_full_range { range_2g = 0, range_4g, range_8g, range_16g };

  enum class gyro_full_range { range_250 = 0, range_500, range_1000, range_2000 };
}  // namespace mpu6050
#endif