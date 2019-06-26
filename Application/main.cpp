#include "../MAX7219-Library/MAX7219.hpp"
#include "../MPU6050-Library/MPU6050.hpp"
#include "../MAX7219-Library/windowDecorator.hpp"

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
  xy total_size(16, 8);
  MAX7219 matrix = MAX7219(size_matrix, clk, din, load, 2, 1);
  MAX7219 matrix2 = MAX7219(size_matrix, clk, din, load, 2, 2);
  matrix.initialize(2);
  array<window*, 2> test = {&matrix, &matrix2};
  auto screen = combine_windows<2>(test, 1, 2, total_size, true);

  auto mpu = mpu6050::MPU6050(i2c_bus);
  mpu.whoAmI();

  int result_x = 0;
  int result_y = 0;

  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 16; x++){
      xy pos(x,y);
      screen.write(pos);
      screen.flush();
    }
    result_x = mpu.getAngleX();
    result_y = mpu.getAngleY();
    cout << "hoek X: " << result_x << " Y: " << result_y << endl;
    if(y == 7) y = -1;
  }
  return 0;
}