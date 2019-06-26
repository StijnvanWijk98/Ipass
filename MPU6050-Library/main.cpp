#include "MPU6050.hpp"

int main() {
  hwlib::wait_ms(500);
  namespace target = hwlib::target;
  auto scl = target::pin_oc(target::pins::d9);
  auto sda = target::pin_oc(target::pins::d8);
  auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

  auto mpu = mpu6050::MPU6050(i2c_bus);
  mpu.readRegister(mpu6050::registers::who_am_i);
  mpu.printReadBuffer();

  // uint16_t testing = mpu.combineRegisters(mpu6050::registers::who_am_i, mpu6050::registers::who_am_i);
  // cout  << "testing: " << testing << endl;
  // uint8_t  rawx = mpu.getAccRawX();
  // cout << "raw x: " << rawx << endl;
  for (;;) {
  //   mpu6050::accData results = mpu.getAccRawAll();
  //   cout << "acc x: " << results.acc_x << endl;
  //   cout << "acc y: " << results.acc_y << endl;
  //   cout << "acc z: " << results.acc_z << endl;

    int result = mpu.getAngleX();
    cout << "Hoek: " << result << endl;
    hwlib::wait_ms(500);
  }
  return 0;
}