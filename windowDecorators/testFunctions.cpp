// ==========================================================================
//
// Author    : Stijn van Wijk
// File      : testFunctions.cpp
// Part of   : C++ hwlib windowdecorator library
// Copyright : stijn.vanwijk@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "testFunctions.hpp"

void testMirrorX(window& base, window& w2) {
  auto mir_x = mirror_x(w2);
  for (int y = 0; y < base.size.y; y++) {
    for (int x = 0; x < base.size.x; x++) {
      base.write(xy(x, y));
      mir_x.write(xy(x, y));
      base.flush();
      mir_x.flush();
      wait_ms(100);
    }
  }
}

void testMirrorY(window& base, window& w2) {
  auto mir_y = mirror_y(w2);
  for (int y = 0; y < base.size.y; y++) {
    for (int x = 0; x < base.size.x; x++) {
      base.write(xy(x, y));
      mir_y.write(xy(x, y));
      base.flush();
      mir_y.flush();
      wait_ms(100);
    }
  }
}

void testDuplicate(window& w1, window& w2) {
  auto dupl = duplicate(w1, w2);
  for (int y = 0; y < dupl.size.y; y++) {
    for (int x = 0; x < dupl.size.x; x++) {
      dupl.write(xy(x, y));
      dupl.flush();
      wait_ms(100);
    }
  }
}

void testCombineWindowsHort(array<window*, 2> arr) {
  xy total_size(16, 8);
  auto comb = combine_windows<2>(arr, 1, 2, total_size, true);
  for (int y = 0; y < comb.size.y; y++) {
    for (int x = 0; x < comb.size.x; x++) {
      comb.write(xy(x, y));
      comb.flush();
      wait_ms(100);
    }
  }
}

void testCombineWindowsVert(array<window*, 2> arr) {
  xy total_size(8, 16);
  auto comb = combine_windows<2>(arr, 2, 1, total_size, true);
  for (int y = 0; y < comb.size.y; y++) {
    for (int x = 0; x < comb.size.x; x++) {
      comb.write(xy(x, y));
      comb.flush();
      wait_ms(100);
    }
  }
}