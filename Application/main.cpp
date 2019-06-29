#include "particle.hpp"

int main() {
  hwlib::wait_ms(500);
  namespace target = hwlib::target;
  auto scl = target::pin_oc(target::pins::scl1);
  auto sda = target::pin_oc(target::pins::sda1);
  auto clk = target::pin_out(target::pins::d5);
  auto load = target::pin_out(target::pins::d6);
  auto din = target::pin_out(target::pins::d7);
  auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

  xy size_matrix(8, 8);
  auto matrix = MAX7219(size_matrix, clk, din, load, 1, 1);
  matrix.initialize();

  auto mpu = mpu6050::MPU6050(i2c_bus);

  particle p1 = particle(xy(5, 4), size_matrix);
  array<particle*, 1> arr = {&p1};

  auto simu = simulation<1>(matrix, mpu, arr);
  simu.drawParticles();

  for (;;) {
    // wait_ms(1000);  // Debug speed
    wait_ms(50);
    simu.updateAcceleration();
    simu.updateParticles();
    simu.drawParticles();
  }

  return 0;
}

// ================ Screentest
// xy size_matrix(8, 8);
// xy total_size(16, 8);
// MAX7219 matrix = MAX7219(size_matrix, clk, din, load, 2, 1);
// MAX7219 matrix2 = MAX7219(size_matrix, clk, din, load, 2, 2);
// matrix.initialize(2);
// array<window*, 2> test = {&matrix, &matrix2};
// auto screen = combine_windows<2>(test, 1, 2, total_size, true);

// ================== Particletest
// particle p1 = particle(xy(5, 4), total_size);
// for (;;) {
//   p1.draw(screen);
//   screen.flush();
//   p1.userInput();
//   p1.updatePosition();
// }

// ================== mpu6050Test
// auto mpu = mpu6050::MPU6050(i2c_bus);
// mpu.whoAmI();

// int result_x = 0;
// int result_y = 0;

// for(;;){
//   result_x = mpu.getAngleX();
//   result_y = mpu.getAngleY();
//   cout << "hoek X: " << result_x << " Y: " << result_y << endl;
// }