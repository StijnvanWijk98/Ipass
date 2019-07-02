#include "MAX7219.hpp"
#include "windowDecorator.hpp"

int main() {
  wait_ms(500);
  namespace target = hwlib::target;
  auto clk = target::pin_out(target::pins::d5);
  auto load = target::pin_out(target::pins::d6);
  auto din = target::pin_out(target::pins::d7);

  xy size_matrix(8, 8);

  MAX7219 matrix = MAX7219(size_matrix, clk, din, load, 2, 1);
  MAX7219 matrix2 = MAX7219(size_matrix, clk, din, load, 2, 2);
  matrix.initialize();
  xy total_size(16, 8);

  // auto mir = mirror_x(matrix);
  // auto mirror = mirror_y(mir);
  // auto testing = duplicate(mirror, matrix2);

  // testing.write(xy(0, 0));
  // testing.flush();

  // =============== combine test
  array<window*, 2> test = {&matrix, &matrix2};
  auto window_arr = combine_windows<2>(test, 1, 2, total_size, true);
  for(int y = 0; y < 8; y++){
    for(int x = 0; x < 16; x++){
      window_arr.write(xy(x,y));
      window_arr.flush();
      wait_ms(50);
    }
    if(y == 7) y = -1;
  }
  return 0;
}
