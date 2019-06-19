#include "MAX7219.hpp"

int main() {
  wait_ms(500);
  namespace target = hwlib::target;
  auto clk = target::pin_out(target::pins::d5);
  auto load = target::pin_out(target::pins::d6);
  auto din = target::pin_out(target::pins::d7);

  xy size_matrix(8, 8);

  MAX7219 matrix = MAX7219(size_matrix, clk, din, load, 2, 1);
  MAX7219 matrix2 = MAX7219(size_matrix, clk, din, load,2, 2);
  matrix.initialize(2);
  wait_ms(500);


  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      matrix.write(xy(j,i));
      matrix.write(xy(i,j));
      matrix.flush();
      matrix2.write(xy(7-i,7-j));
      matrix2.write(xy(7-j,7-i));
      matrix2.flush();
    }
    if (i == 7) i = -1;
  }

  return 0;
}
