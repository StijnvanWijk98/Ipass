#include "particle.hpp"

void particle::updateSpeed(const xyDouble& acceleration) {
  if ((real_pos.x <= 0 && acceleration.x < 0) || (real_pos.x >= x_max && acceleration.x > 0)) {
    // cout << "speed in x" << endl;
    speed.x = 0.0;
  } else {
    speed.x = speed.x + acceleration.x;
  }
  if ((real_pos.y <= 0 && acceleration.y < 0) || (real_pos.y >= y_max && acceleration.y > 0)) {
    // cout << "speed in y" << endl;
    speed.y = 0.0;
  } else {
    speed.y = speed.y + acceleration.y;
  }
  // int speed_x_print = speed.x;
  // int speed_y_print = speed.y;
  // cout << "Speed X: " << speed_x_print << " Y: " << speed_y_print << endl;
}

void particle::updatePosition() {
  double new_x = real_pos.x + speed.x;
  double new_y = real_pos.y + speed.y;
  if (new_x > x_max) {
    new_x = x_max;
  } else if (new_x < 0) {
    new_x = 0;
  }
  if (new_y > y_max) {
    new_y = y_max;
  } else if (new_y < 0) {
    new_y = 0;
  }
  real_pos.x = new_x;
  real_pos.y = new_y;
  // int real_pos_x_print = real_pos.x;
  // int real_pos_y_print = real_pos.y;
  // cout << "real_pos X: " << real_pos_x_print << " Y: " << real_pos_y_print << endl;
}

void particle::draw(window& w) {
  start.x = real_pos.x;
  start.y = real_pos.y;
  w.write(start);
}

void particle::userInput() {
  namespace target = hwlib::target;
  auto but1 = target::pin_in(target::pins::d8);
  auto but2 = target::pin_in(target::pins::d9);
  auto but3 = target::pin_in(target::pins::d10);
  auto but4 = target::pin_in(target::pins::d11);
  bool input = false;

  while (!input) {
    but1.refresh();
    but2.refresh();
    but3.refresh();
    but4.refresh();

    if (!but1.read()) {
      speed.y = -1;
      input = true;
    }
    if (!but2.read()) {
      speed.x = -1;
      input = true;
    }
    if (!but3.read()) {
      speed.x = 1;
      input = true;
    }
    if (!but4.read()) {
      speed.y = 1;
      input = true;
    }
  }
}