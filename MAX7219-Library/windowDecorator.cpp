#include "windowDecorator.hpp"

void duplicate::clear() {
  slave0.clear();
  slave1.clear();
}

void duplicate::flush() {
  slave0.flush();
  slave1.flush();
}

void duplicate::write_implementation(xy pos, color col) {
  slave0.write(pos, col);
  slave1.write(pos, col);
}

void mirror_x::write_implementation(xy pos, color col) {
  int new_x = (size.x - 1) - pos.x;
  slave.write(xy(new_x, pos.y));
}
void mirror_x::clear() { slave.clear(); }
void mirror_x::flush() { slave.flush(); }

void mirror_y::write_implementation(xy pos, color col) {
  int new_y = (size.y - 1) - pos.y;
  slave.write(xy(pos.x, new_y));
}
void mirror_y::clear() { slave.clear(); }
void mirror_y::flush() { slave.flush(); }