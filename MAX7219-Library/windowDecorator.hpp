#ifndef WINDOWDECORATOR_HPP
#define WINDOWDECORATOR_HPP

#include "hwlib.hpp"
using hwlib::color;
using hwlib::window;
using hwlib::xy;
using std::array;

/// @file

/// \brief
///
/// \details
///
///
///
class duplicate : public window {
 private:
  window& slave0;
  window& slave1;

  /// \brief
  ///
  /// \details
  ///
  ///
  ///
  void write_implementation(xy pos, color col) override;

 public:
  /// \brief
  ///
  /// \details
  ///
  ///
  ///
  duplicate(window& window0, window& window1) : window(window0.size), slave0(window0), slave1(window1) {}

  /// \brief
  ///
  /// \details
  ///
  ///
  ///
  void clear() override;

  /// \brief
  ///
  /// \details
  ///
  ///
  ///
  void flush() override;
};

class mirror_x : public window {
 private:
  window& slave;

  /// \brief
  ///
  /// \details
  ///
  ///
  ///
  void write_implementation(xy pos, color col) override;

 public:
  /// \brief
  ///
  /// \details
  ///
  ///
  ///
  mirror_x(window& window0) : window(window0.size), slave(window0) {}

  /// \brief
  ///
  /// \details
  ///
  ///
  ///
  void flush() override;

  /// \brief
  ///
  /// \details
  ///
  ///
  ///
  void clear() override;
};

class mirror_y : public window {
 private:
  window& slave;

  /// \brief
  ///
  /// \details
  ///
  ///
  ///
  void write_implementation(xy pos, color col) override;

 public:
  mirror_y(window& window0) : window(window0.size), slave(window0) {}

  /// \brief
  ///
  /// \details
  ///
  ///
  ///
  void flush() override;

  /// \brief
  ///
  /// \details
  ///
  ///
  ///
  void clear() override;
};

template <unsigned int N>
/// \brief
///
/// \details
///
///
///
class combine_windows : public window {
 private:
  array<window*, N> windows;
  int num_rows, num_columns;
  bool uniform_size;

  /// \brief
  ///
  /// \details
  ///
  ///
  ///
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
  ///
  /// \details
  ///
  ///
  ///
  combine_windows(const array<window*, N> windows, int num_rows, int num_column, xy total_size, bool uniform_size)
      : window(total_size), windows(windows), num_rows(num_rows), num_columns(num_column), uniform_size(uniform_size) {}

  /// \brief
  ///
  /// \details
  ///
  ///
  ///
  void clear() override {
    for (unsigned int i = 0; i < N; i++) {
      windows[i]->clear();
    }
  }

  /// \brief
  ///
  /// \details
  ///
  ///
  ///
  void flush() override {
    for (unsigned int i = 0; i < N; i++) {
      windows[i]->flush();
    }
  }
};

#endif