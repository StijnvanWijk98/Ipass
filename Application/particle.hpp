// ==========================================================================
//
// Author    : Stijn van Wijk
// File      : particle.hpp
// Part of   : C++ physics simulator library
// Copyright : stijn.vanwijk@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

// NOTE: All the mathematics are thanks to Ruben Vink

#include "../MAX7219-Library/MAX7219.hpp"
#include "../windowDecorators/windowDecorator.hpp"
#include "../MPU6050-Library/MPU6050.hpp"
#include "hwlib.hpp"

using hwlib::cout;
using hwlib::drawable;
using hwlib::endl;
using hwlib::now_us;
using hwlib::window;
using hwlib::xy;
using std::array;
using std::max;

/// @file

/// \brief
/// Vector ADT
/// \details
/// This is an ADT that implements a vector based on floats.\n
/// The vector contains two floats.\n
/// It contains the needed operators to be used in the application.
class vector {
 public:
  float x;
  float y;

  /// \brief
  /// Add vector with vector
  /// \details
  /// This operator adds two vectors.\n
  /// The operator adds the x and y of the two vectors.\n
  /// It returns a new vector.
  vector operator+(const vector& rhs) const;

  /// \brief
  /// Multiply vector with integer
  /// \details
  /// This operator multiplies a vector with an integer.\n
  /// It will multiply both the x and y value with the integer.\n
  /// The answer is saved in the vector, left of the equation.
  vector& operator*=(const int& rhs);

  /// \brief
  /// Multiply vector with vector
  /// \details
  /// This operator multiplies a vector with another vector.\n
  /// The x and y values of the vectors are multiplied with eachother.\n
  /// It returns a new vector.
  vector operator*(const vector& rhs) const;

  /// \brief
  /// Multiply vector with float
  /// \details
  /// This operator multiplies a vector with a float.\n
  /// It will multiply both the x and y value with the float.\n
  /// It returns a new vector.
  vector operator*(const float& rhs) const;

  /// \brief
  /// Compare two vectors
  /// \details
  /// This operator test for equality.\n
  /// It returns true if and only if the x and y of both vectors are equal.
  bool operator==(const vector& rhs) const;

  /// \brief
  /// Multiply float with vector
  /// \details
  /// This operator multiplies a float with a vector.\n
  /// It will multiply both the x and y value with the float.\n
  /// It returns a new vector.
  friend vector operator*(const float& lhs, const vector& rhs) { return vector{lhs * rhs.x, lhs * rhs.y}; }

  /// \brief
  /// output operator vector to hwlib::ostream
  /// \details
  /// This operator streams the vector to a hwlib::ostream.\n
  /// The operator will give the following result in the ostream: (x,y)\n
  /// The x and y values are printed in a 7 decimal precision.
  friend hwlib::ostream& operator<<(hwlib::ostream& lhs, const vector& rhs) {
    int x_base = rhs.x;
    int y_base = rhs.y;
    int x_dec = abs((rhs.x - x_base) * 1e7);  // 1e7 is the presicion amount
    int y_dec = abs((rhs.y - y_base) * 1e7);
    lhs << '(' << x_base << '.' << x_dec << ',' << y_base << '.' << y_dec << ')';
    return lhs;
  }

  // NOT NEEDED!!!!!!!!!!!!!!!!

  /// \brief
  /// output operator vector to std::ostream
  /// \details
  /// This operator streams the vector to a std::ostream.\n
  /// The operator will give the following result in the ostream: (x,y)\n
  /// The x and y values are printed in a 7 decimal precision.
  // friend std::ostream& operator<<(std::ostream& lhs, const vector& rhs) {
  //   int x_base = rhs.x;
  //   int y_base = rhs.y;
  //   int x_dec = abs((rhs.x - x_base) * 1e7);  // 1e7 is the presicion amount
  //   int y_dec = abs((rhs.y - y_base) * 1e7);
  //   lhs << '(' << x_base << '.' << x_dec << ',' << y_base << '.' << y_dec << ')';
  //   return lhs;
  // }

  /// \brief
  /// Magnitude vector
  /// \details
  /// This function returns the magnitude of the vector.\n
  /// In other words, it returns the length of the vector.\n
  /// The magnitude is the sqrt(sq(x)+sq(y)).
  /// Call example: float magn = vector.magnitude();
  float magnitude();

  /// \brief
  /// Magnitude squared vector
  /// \details
  /// This function returns the magnitude squared.\n
  /// Call example: float sqmagn = vector.magnitude();
  float squaredMagnitude();

  /// \brief
  /// Norm of vector
  /// \details
  /// This function returns the norm of the vector.\n
  /// Call example: auto norm = vector.norm();
  /// More information about the norm can you find on:\n
  /// https://en.wikipedia.org/wiki/Norm_(mathematics)
  vector norm();
};

/// \brief
/// Particle ADT
/// \details
/// This is a particle class, is meant to be used in the simulation class./n
/// A particle is based on hwlib drawable.\n
/// The needed functions and constructor are provided.
class particle : public drawable {
 private:
  vector speed = {0.0, 0.0};  // The speed of the particle
  vector real_pos;            // This variabele is the real pos of the particle
  int x_max;                  // max x-position of the particle
  int y_max;                  // max y-position of the particle
  float d_max;                // Distance from corner to the middle op the window
  float radius;               // The radius of the particle

 public:
  /// \brief
  /// Constructor particle
  /// \details
  /// The constructor creates a particle object.\n
  /// You are obligated to give a start_pos (xy), size_simulation (xy).\n
  /// You can change the radius of the particle, but this is not advised when used with simulation.\n
  /// Call example: auto part = particle(xy(2,2), xy(8,8));
  particle(const xy& start_pos, const xy& size_simulation, float radius = 0.5) : drawable(start_pos), radius(radius) {
    x_max = size_simulation.x;
    y_max = size_simulation.y;
    real_pos.x = start_pos.x;
    real_pos.y = start_pos.y;
    d_max = (0.25 * x_max * x_max) + (0.25 * y_max * y_max);
  }

  /// \brief
  /// Update speed vector
  /// \details
  /// This function updates the speed of particle./n
  /// It expects a acceleration (vector), delta_time (double) and a resis_const (float)\n
  /// The function uses physics calculations to determine the speed.\n
  /// A more detailed explenation can be found by the implementation.\n
  /// Call example: part.updateSpeed(vector{1.0,3.5}, 0.2, 0.14);
  void updateSpeed(const vector& acceleration, const double& delta_time, const float& resis_const);

  /// \brief
  /// Draw particle
  /// \details
  /// This function draws the particle on the screen.\n
  /// You are obligated to give a window&.\n
  /// This function calls the write function of the given window.\n
  /// Call example: part.draw(window);
  void draw(window& w) override;

  /// \brief
  /// Get real_pos
  /// \details
  /// This function returns the real_pos of the particle.\n
  /// Call example: auto other_real_pos = part.getRealPos();
  vector getRealPos();

  template <unsigned int N>
  /// \brief
  /// Update position
  /// \details
  /// This function updates the position of the particle.\n
  /// It does two checks, collision with other particles and out of bounce.
  /// You are obligated to give delta_time (double), particles (array), id(int).\n
  /// When the particle collides with another particle, the position doesn't change.\n
  ///  If collided, speed is {0.0,0.0}.\n
  /// When the ball is out of bounce on one of the axis, the position is set to the exact min or max.\n
  /// The speed is also set to 0 on the corresponding axis.\n
  /// Call example: part.updatePosition(0.25, arr, 2);
  void updatePosition(const double& delta_time, const array<particle*, N>& particles, unsigned int id) {
    float new_x = real_pos.x + (speed.x * delta_time);  // New x-position of the particle
    float new_y = real_pos.y + (speed.y * delta_time);  // New y-position of the particle
    // =================== Collision ==========================
    for (unsigned int i = id + 1; i < N; i++) {  // Only check for collisions with particles that are not checked yet
      vector pos_comp = particles[i]->getRealPos();
      // Calculate the distance between the two particles.
      float distance = ((pos_comp.x - real_pos.x) * (pos_comp.x - real_pos.x)) +
                       ((pos_comp.y - real_pos.y) * (pos_comp.y - real_pos.y));
      if (distance < 1) {  // The 1 is the radius+radius squared
                           // If true than there is a collision, so position doesn't change
        new_x = real_pos.x;
        new_y = real_pos.y;
        speed = {0.0, 0.0};
        break;
      }
    }
    if (new_x > x_max - radius) {  // Checks if new_x is out of bounce
      new_x = x_max - radius;
      speed.x = 0;
    } else if (new_x < 0 + radius) {
      new_x = 0 + radius;
      speed.x = 0;
    }
    if (new_y > y_max - radius) {  // Checks if new_y is out of bounce
      new_y = y_max - radius;
      speed.y = 0;
    } else if (new_y < 0 + radius) {
      new_y = 0 + radius;
      speed.y = 0;
    }
    real_pos.x = new_x;  // No collision or out of bounce, so new_x is oke
    real_pos.y = new_y;  // No collision or out of bounce, so new_y is oke
  }
};

template <unsigned int N>
/// \brief
/// Simulation ADT
/// \details
/// This is the simulation class, it simulates one or multiple particles on a window.\n
/// It calculates an acceleration (vector), which is used to update the speed of the particles.\n
/// The class can contain a n number of particles. An increase in particles can harm the peformance.\n
/// The needed functions and constructor are provided.
class simulation {
 private:
  hwlib::window& window;  // Window where particles will be draw on.
  xy size;                // Size of the simulation
  MPU6050& mpu;           // Sensor where acceleration is based on
  array<particle*, N> particles;
  vector acceleration = {0.0, 0.0};
  float max_acceleration;  // The maximum acceleration possible in simulation
  int accel_threshold;     // Threshold before angle measurment is used to calculate acceleration
  float max_speed;         // Max speed of particles in simulation
  uint64_t previous_time;  // Used to calculate the delta_time
  float resis_const;       // resistance const calculated based on max_acceleration and max_speed

 public:
  /// \brief
  /// Constructor simulation
  /// \details
  /// This constructor creates a simulation object.\n
  /// You are obligated to give w (window&), mpu (MPU6050&), particles (array).\n
  /// You can change the max_accel, accel_threshold and max_speed but this not necessary.\n
  /// A change in max_accel or max_speed will change the behaviour of the particles in the simulation.\n
  /// A change in threshold will make the simulation more or less sensitive.\n
  /// Call example: auto simu = simulation(window, mpu, arr_particles, 50, 6);
  simulation(hwlib::window& w, MPU6050& mpu, const array<particle*, N>& particles, float max_accel = 30,
             unsigned int accel_thresh = 10, float max_speed = 8)
      : window(w),
        size(w.size),
        mpu(mpu),
        particles(particles),
        max_acceleration(max_accel),
        accel_threshold(accel_thresh),
        max_speed(max_speed) {
    previous_time = now_us();
    resis_const = max_acceleration / (max_speed * max_speed);
  }

  /// \brief
  /// Update acceleration
  /// \details
  /// This function updates the acceleration of the simulation.\n
  /// If the angle given by the MPU6050 is above the threshold, than it calculates the acceleration.\n
  /// The acceleration is never greater than max_acceleration.\n
  /// Call example: simu.updateAcceleration();
  void updateAcceleration() {
    int angle_x = mpu.getAngleX();
    int angle_y = mpu.getAngleY();
    if (angle_x > accel_threshold || angle_x < -accel_threshold) {
      acceleration.x = (max_acceleration * (angle_x / 90.0));
    } else {
      acceleration.x = 0;
    }
    if (angle_y > accel_threshold || angle_y < -accel_threshold) {
      acceleration.y = -1 * (max_acceleration * (angle_y / 90.0));
    } else {
      acceleration.y = 0;
    }
  }

  /// \brief
  /// Update particles
  /// \details
  /// This function updates the speed and position of all the particles.\n
  /// First it update the speed of all the particles and then it will update the position.\n
  /// Call example: simu.updateParticles();
  void updateParticles() {
    uint64_t current_time = now_us();
    double d_time = (current_time - previous_time) / 1e6;  // current_time is in nanoseconds
    previous_time = current_time;
    for (unsigned int i = 0; i < N; i++) {
      particles[i]->updateSpeed(acceleration, d_time, resis_const);
    }
    for (unsigned int i = 0; i < N; i++) {
      particles[i]->updatePosition(d_time, particles, i);
    }
  }

  /// \brief
  /// Draw particles
  /// \details
  /// This function will draw all the particles on the window.\n
  /// Call example: simu.drawParticles();
  void drawParticles() {
    for (unsigned int i = 0; i < N; i++) {
      particles[i]->draw(window);
    }
    window.flush();
  }

  /// \brief
  /// Simulation loop
  /// \details
  /// This function loops through both update and draw function.\n
  /// When all you wanna do is run the simulation you can call this function.\n
  /// The function contains an endless loop, so keep that in mind.\n
  /// Call example: simu.simulationLoop();
  void simulationLoop() {
    while (true) {
      updateAcceleration();
      updateParticles();
      drawParticles();
    }
  }
};