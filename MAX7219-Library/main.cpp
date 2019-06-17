#include "MAX7219.hpp"

int main() {
  wait_ms(500);
  namespace target = hwlib::target;
  auto clk = target::pin_out(target::pins::d10);
  auto din = target::pin_out(target::pins::d8);
  auto load = target::pin_out(target::pins::d9);

  xy size_matrix(8, 8);
  xy test_loc(7,7);
  // xy test_loc2(7, 2);

  MAX7219 matrix = MAX7219(size_matrix, clk, din, load);
  matrix.initialize();

  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      xy point(j,i);
      matrix.write(point);
      matrix.flush();
      wait_ms(50);
    }
    if(i == 7) i = -1;
  }

  return 0;
}
