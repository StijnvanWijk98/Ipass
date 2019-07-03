#include "testFunctions.hpp"

int main() {
  /* The program showcases some of the basic functionality of the decorators.
   * The functions used can be found in testFunctions.hpp and testFunctions.cpp
   * For a complete overlook what the decorators can do, view the doxygen included with the decorators.
   */
  wait_ms(500);
  namespace target = hwlib::target;
  auto clk = target::pin_out(target::pins::d5);
  auto load = target::pin_out(target::pins::d6);
  auto din = target::pin_out(target::pins::d7);

  xy size_matrix(8, 8);
  auto matrix = MAX7219(size_matrix, clk, din, load, 2, 1);
  auto matrix2 = MAX7219(size_matrix, clk, din, load, 2, 2);
  matrix.initialize();
  matrix.clear();
  matrix2.clear();

  array<window*, 2> test_array{&matrix, &matrix2};


  // ==== TEST: mirror_x
  testMirrorX(matrix, matrix2);
  wait_ms(500);
  // ==== TEST: mirror_y
  testMirrorY(matrix, matrix2);
  wait_ms(500);
  // ==== TEST: duplicate
  testDuplicate(matrix, matrix2);
  wait_ms(500);
  // ==== TEST: combine horizontal
  testCombineWindowsHort(test_array);
  wait_ms(500);
  // ==== TEST: combine vertical
  testCombineWindowsVert(test_array);

  return 0;
}
