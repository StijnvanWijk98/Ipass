// ==========================================================================
//
// Author    : Stijn van Wijk
// File      : particle.cpp
// Part of   : C++ physics simulator library
// Copyright : stijn.vanwijk@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "particle.hpp"

vector vector::operator+(const vector& rhs) const { return vector{(x + rhs.x), (y + rhs.y)}; }

vector& vector::operator*=(const int& rhs) {
  x *= rhs;
  y *= rhs;
  return *this;
}
vector vector::operator*(const vector& rhs) const { return vector{x * rhs.x, y * rhs.y}; }

vector vector::operator*(const float& rhs) const { return vector{x * rhs, y * rhs}; }

bool vector::operator==(const vector& rhs) const { return ((x == rhs.x) && (y == rhs.y)); }

float vector::magnitude() { return sqrt((x * x) + (y * y)); }
float vector::squaredMagnitude() { return ((x * x) + (y * y)); }

vector vector::norm() {
  float eps = 0.001;
  float mag = magnitude();
  if (mag < eps) mag = eps;
  return *this * (1 / magnitude());
}

vector particle::getRealPos() { return real_pos; }

void particle::updateSpeed(const vector& acceleration, const double& delta_time, const float& resis_const) {
  // Calculate the distance between the particle and middle of field
  float d_middle = ((real_pos.x - x_max * 0.5) * (real_pos.x - x_max * 0.5)) +
                   ((real_pos.y - y_max * 0.5) * (real_pos.y - y_max * 0.5));
  float modifier = ((d_max - d_middle) / d_max) * 0.9 + 0.1;  // Closer to the center is greater acceleration.
  // The modifier makes it easier for particles that are bunched up in a corner to escape.
  vector a_resistance = speed * speed.magnitude() * resis_const;  // The resistance on the particle
  speed.x = speed.x + ((acceleration.x - a_resistance.x) * delta_time * modifier);
  speed.y = speed.y + ((acceleration.y - a_resistance.y) * delta_time * modifier);
}

void particle::draw(window& w) {
  start.x = real_pos.x;
  start.y = real_pos.y;
  w.write(start);
}