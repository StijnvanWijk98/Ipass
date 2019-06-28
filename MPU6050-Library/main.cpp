#include "MPU6050.hpp"

int main() {
  hwlib::wait_ms(500);
  namespace target = hwlib::target;
  auto scl = target::pin_oc(target::pins::scl1);
  auto sda = target::pin_oc(target::pins::sda1);
  auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

  auto mpu = mpu6050::MPU6050(i2c_bus);
  mpu.whoAmI();
  mpu.calibrate();

  for (;;) {
    // mpu6050::accData results_acc = mpu.getAccAll();
    // cout << "acc x: " << results_acc.acc_x << endl;
    // cout << "acc y: " << results_acc.acc_y << endl;
    // cout << "acc z: " << results_acc.acc_z << endl;

    // mpu6050::gyroData results_gyro = mpu.getGyroAll();
    // cout << "gyro x: " << results_gyro.gyro_x << endl;
    // cout << "gyro y: " << results_gyro.gyro_y << endl;
    // cout << "gyro z: " << results_gyro.gyro_z << endl;

    int result_x = mpu.getAngleX();
    int result_y = mpu.getAngleY();
    cout << "hoek X: " << result_x << " Y: " << result_y << endl;
    hwlib::wait_ms(2000);
  }
  return 0;
}