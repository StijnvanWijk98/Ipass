// ==========================================================================
//
// Author    : Stijn van Wijk
// File      : testFunctions.cpp
// Part of   : C++ MAX7219 library
// Copyright : stijn.vanwijk@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "testFunctions.hpp"

void testBlinkScreen(window& w) {
  for (int i = 0; i < 10; i++) {
    for (int y = 0; y < w.size.y; y++) {
      for (int x = 0; x < w.size.x; x++) {
        w.write(xy(x, y));
      }
    }
    w.flush();
    wait_ms(500);
    w.clear();
    wait_ms(500);
  }
}

void testScrollPixel(window& w) {
  for (int y = 0; y < w.size.y; y++) {
    for (int x = 0; x < w.size.x; x++) {
      w.write(xy(x, y));
      w.flush();
      wait_ms(100);
    }
  }
}