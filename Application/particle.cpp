#include "particle.hpp"

void particle::updatePosition() {
  int new_x = start.x + speed.x;
  int new_y = start.y + speed.y;
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
  start.x = new_x;
  start.y = new_y;
}

void particle::updateSpeed(const xy& acceleration) {
  if ((start.x < 0 && acceleration.x < 0) || (start.x == x_max && acceleration.x > 0)) {
    speed.x = 0;
  } else {
    speed.x = speed.x + acceleration.x;
  }
  if ((start.y < 0 && acceleration.y < 0) || (start.y == y_max && acceleration.y > 0)) {
    speed.y = 0;
  } else {
    speed.y = speed.y + acceleration.y;
  }
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

void particle::draw(window& w) { w.write(start); }