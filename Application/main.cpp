#include "particle.hpp"

int main() {
  /* The program showcases some a implementation of a physics simulator.
   */
  hwlib::wait_ms(500);
  namespace target = hwlib::target;
  auto scl = target::pin_oc(target::pins::scl1);
  auto sda = target::pin_oc(target::pins::sda1);
  auto clk1 = target::pin_out(target::pins::d8);
  auto load1 = target::pin_out(target::pins::d9);
  auto din1 = target::pin_out(target::pins::d10);
  auto clk2 = target::pin_out(target::pins::d5);
  auto load2 = target::pin_out(target::pins::d6);
  auto din2 = target::pin_out(target::pins::d7);
  auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

  xy size_total(32, 16);
  xy size(8, 8);
  auto matrix = MAX7219(size, clk1, din1, load1, 4, 1);
  auto matrix2 = MAX7219(size, clk1, din1, load1, 4, 2);
  auto matrix3 = MAX7219(size, clk1, din1, load1, 4, 3);
  auto matrix4 = MAX7219(size, clk1, din1, load1, 4, 4);
  auto matrix5 = MAX7219(size, clk2, din2, load2, 4, 1);
  auto matrix6 = MAX7219(size, clk2, din2, load2, 4, 2);
  auto matrix7 = MAX7219(size, clk2, din2, load2, 4, 3);
  auto matrix8 = MAX7219(size, clk2, din2, load2, 4, 4);
  matrix.initialize();
  matrix5.initialize();

  array<window*, 8> windows = {&matrix, &matrix2, &matrix3, &matrix4, &matrix5, &matrix6, &matrix7, &matrix8};
  auto screen = combine_windows<8>(windows, 2, 4, size_total, true);
  screen.clear();

  auto mpu = MPU6050(i2c_bus);
  mpu.whoAmI();
  mpu.calibrate();

  particle p0 = particle(xy(1, 1), size_total);
  particle p1 = particle(xy(2, 1), size_total);
  particle p2 = particle(xy(3, 1), size_total);
  particle p3 = particle(xy(4, 1), size_total);
  particle p4 = particle(xy(5, 1), size_total);
  particle p5 = particle(xy(1, 2), size_total);
  particle p6 = particle(xy(2, 2), size_total);
  particle p7 = particle(xy(3, 2), size_total);
  particle p8 = particle(xy(4, 2), size_total);
  particle p9 = particle(xy(5, 2), size_total);
  array<particle*, 10> arr = {&p0, &p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9};

  auto simu = simulation<10>(screen, mpu, arr, 30);
  simu.drawParticles();

  for (;;) {
    simu.updateAcceleration();
    simu.updateParticles();
    simu.drawParticles();
  }

  return 0;
}