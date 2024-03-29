// ==========================================================================
//
// Author    : Stijn van Wijk
// File      : windowDecorator.hpp
// Part of   : C++ hwlib windowdecorator library
// Copyright : stijn.vanwijk@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#ifndef WINDOWDECORATOR_HPP
#define WINDOWDECORATOR_HPP

#include "hwlib.hpp"
using hwlib::color;
using hwlib::window;
using hwlib::xy;
using std::array;

/// @file

/// \brief
/// Decorator duplicate window
/// \details
/// This class is a decorator that duplicates two windows.\n
/// If you write to a duplicate window it will be shown on two windows.
class duplicate : public window {
 private:
  window& slave0;
  window& slave1;

  /// \brief
  /// write a pixel - implementation
  /// \details
  /// This function writes the given pos and color to the two slave windows.
  void write_implementation(xy pos, color col) override;

 public:
  /// \brief
  /// Create a duplicate window from two windows
  /// \details
  /// This constructor creates a window from two windows.\n
  /// You are obligated to give two windows.\n
  /// The size of the created window, is the windowsize of the first window (slave0).\n
  /// The fore- and backgound is the same as the first window (slave0).\n
  /// Call example: window screen = duplicate(window0, window1);
  duplicate(window& window0, window& window1)
      : window(window0.size, window0.foreground, window0.background), slave0(window0), slave1(window1) {}

  /// \brief
  /// Clear the window
  /// \details
  /// This function calls the clear-function on both slaves.\n
  /// Call example: screen.clear();
  void clear() override;

  /// \brief
  /// Flush the window
  /// \details
  /// This function calls the flush-function on both slaves.\n
  /// Call example: screen.flush();
  void flush() override;
};

/// \brief
/// Window mirrored X-axis
/// \details
/// This class is a decorator that mirrors a window.\n
/// This window is mirrored in the X-axis.
class mirror_x : public window {
 private:
  window& slave;

  /// \brief
  /// Write a pixel - implementation
  /// \details
  /// This function writes the given pos and col to the window.\n
  /// The X-coor is mirrored.
  void write_implementation(xy pos, color col) override;

 public:
  /// \brief
  /// Create a mirrored window on X-axis
  /// \details
  /// This constructor creates a mirrored window from a window.\n
  /// The created window is mirrored in the X-axis.\n
  /// The size, fore- and background of the window is the same as the given window.\n
  /// Call example: window screen = mirror_x(window);
  mirror_x(window& window0) : window(window0.size, window0.foreground, window0.background), slave(window0) {}

  /// \brief
  /// Clear the window
  /// \details
  /// This function calls the clear-function on the slave.\n
  /// Call example: screen.clear();
  void clear() override;

  /// \brief
  /// Flush the window
  /// \details
  /// This function calls the flush-function on the slave.\n
  /// Call example: screen.flush();
  void flush() override;
};

/// \brief
/// Window mirrored Y-axis
/// \details
/// This class is a decorator that mirrors a window.\n
/// This window is mirrored in the Y-axis.
class mirror_y : public window {
 private:
  window& slave;

  /// \brief
  /// Write a pixel - implementation
  /// \details
  /// This function writes the given pos and col to the window.\n
  /// The Y-coor is mirrored.
  void write_implementation(xy pos, color col) override;

 public:
  /// \brief
  /// Create a mirrored window on Y-axis
  /// \details
  /// This constructor creates a mirrored window from a window.\n
  /// The created window is mirrored in the Y-axis.\n
  /// The size, fore- and background of the window is the same as the given window.\n
  /// Call example: window screen = mirror_y(window);
  mirror_y(window& window0) : window(window0.size, window0.foreground, window0.background), slave(window0) {}

  /// \brief
  /// Flush the window
  /// \details
  /// This function calls the flush-function on the slave.\n
  /// Call example: screen.clear();
  void clear() override;

  /// \brief
  /// Clear the window
  /// \details
  /// This function calls the clear-function on the slave.\n
  /// Call example: screen.flush();
  void flush() override;
};

template <unsigned int N>
/// \brief
/// Combine n*n windows
/// \details
/// This class is a decorator that combines n*n windows to one window.\n
/// You can use different size of windows to combine.\n
/// The amount of columns per row must be the same.\n
/// The windows are in a grid.
class combine_windows : public window {
 private:
  array<window*, N> windows;
  int num_rows, num_columns;
  bool uniform_size;

  /// \brief
  /// write a pixel - implementation
  /// \details
  /// This function writes the given pos and col to the correct window and pos on that screen.\n
  /// When the windows are uniform size, the search for the window is faster.\n
  /// Otherwise the program checks for every window if the pos falls in the size of the window.\n
  void write_implementation(xy pos, color col) override {
    int final_row = 0;
    int final_column = 0;
    int current_size_x = 0;
    int current_size_y = 0;
    if (uniform_size) {
      current_size_x = windows[0]->size.x;
      current_size_y = windows[0]->size.y;
      final_row = pos.y / current_size_y;
      final_column = pos.x / current_size_x;
      int final_x = pos.x % current_size_x;
      int final_y = pos.y % current_size_y;
      pos = xy(final_x, final_y);
    } else {
      bool found_x = false, found_y = false;
      int check_index = 0;

      while (!found_x || !found_y) {
        current_size_x = windows[check_index]->size.x;
        current_size_y = windows[check_index]->size.y;

        if (pos.x > current_size_x - 1) {
          final_column++;
          pos = pos - xy(current_size_x, 0);
        } else {
          found_x = true;
        }
        if (pos.y > current_size_y - 1) {
          final_row++;
          pos = pos - xy(0, current_size_y);
        } else {
          found_y = true;
        }
        check_index++;
      }
    }
    int final_screen = final_column + (final_row * num_columns);
    windows[final_screen]->write(pos);
  }

 public:
  /// \brief
  /// Create a window from n*n windows
  /// \details
  /// This constructor creates a window from a n*n number of windows.\n
  /// You are obligated to give the size of the new window you want to create.\n
  /// You also need to give the amount of rows and columns.\n
  /// If the windows are all the same size, than uniform_size should be true.\n
  /// Call example: window screen = combine_windows(arr, 2, 2, xy(16,16), true);
  combine_windows(const array<window*, N> windows, int num_rows, int num_column, xy total_size,
                  bool uniform_size = false)
      : window(total_size), windows(windows), num_rows(num_rows), num_columns(num_column), uniform_size(uniform_size) {}

  /// \brief
  /// Clear the window
  /// \details
  /// This window calls the clear-function on all the windows.\n
  /// Call example: screen.clear();
  void clear() override {
    for (unsigned int i = 0; i < N; i++) {
      windows[i]->clear();
    }
  }

  /// \brief
  /// Flush the window
  /// \details
  /// This window calls the flush-function on all the windows.\n
  /// Call example: screen.flush();
  void flush() override {
    for (unsigned int i = 0; i < N; i++) {
      windows[i]->flush();
    }
  }
};

#endif