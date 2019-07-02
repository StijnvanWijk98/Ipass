#include "particle.hpp"

void particle::updateSpeed(const xyFloat& acceleration, const double& delta_time, const float& resistance_const) {
  float d_middle = ((real_pos.x - x_max * 0.5) * (real_pos.x - x_max * 0.5)) +
                   ((real_pos.y - y_max * 0.5) * (real_pos.y - y_max * 0.5));
  float modifier = ((d_max - d_middle) / d_max) * 0.9 + 0.1;
  xyFloat a_resistance = speed * speed.magnitude() * resistance_const;
  //(-1.0 * speed.norm() * resistance_const * speed.squaredMagnitude());
  speed.x = speed.x + ((acceleration.x - a_resistance.x) * delta_time * modifier);
  speed.y = speed.y + ((acceleration.y - a_resistance.y) * delta_time * modifier);
  // cout << "a_resitance:" << a_resistance << "\n";
  // cout << "Speed: " << speed << "\n";
}

void particle::draw(window& w) {
  start.x = real_pos.x;
  start.y = real_pos.y;
  w.write(start);
}