#include "testFunctions.hpp"

int main() {
  /* The program showcases some of the basic functionality of the library.
   * The functions used can be found in testFunctions.hpp and testFunctions.cpp
   * For a complete overlook what the library can do, view the doxygen included with the library.
   */
  wait_ms(500);
  namespace target = hwlib::target;
  auto clk = target::pin_out(target::pins::d5);
  auto load = target::pin_out(target::pins::d6);
  auto din = target::pin_out(target::pins::d7);

  xy size_matrix(8, 8);
  auto screen = MAX7219(size_matrix, clk, din, load, 1, 1);
  screen.initialize();

  // ==== TEST: Blinkscreen
  testBlinkScreen(screen);
  // ==== TEST: Scroll pixel
  testScrollPixel(screen);

  return 0;
}
