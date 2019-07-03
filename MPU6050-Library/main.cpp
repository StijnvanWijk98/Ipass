#include "testFunctions.hpp"

int main() {
  /* The program showcases some of the basic functionality of the library.
   * The functions used can be found in testFunctions.hpp and testFunctions.cpp
   * For a complete overlook what the library can do, view the doxygen included with the library.
   */
  wait_ms(500);
  namespace target = hwlib::target;
  auto scl = target::pin_oc(target::pins::scl1);
  auto sda = target::pin_oc(target::pins::sda1);
  auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

  auto mpu = MPU6050(i2c_bus);

  // ==== TEST: angleX
  testAngleX(mpu);
  wait_ms(500);
  // ==== TEST: angleY
  testAngleY(mpu);
  wait_ms(500);
  // ==== TEST: gyroX
  testGyroX(mpu);
  wait_ms(500);
  // ==== TEST: gyroY
  testGyroY(mpu);
  wait_ms(500);
  // ==== TEST: gyroZ
  testGyroZ(mpu);
  wait_ms(500);
  return 0;
}