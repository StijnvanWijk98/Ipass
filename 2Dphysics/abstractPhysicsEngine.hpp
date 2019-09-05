#ifndef ABSTRACTPHYSICSENGINE_HPP
#define ABSTRACTPHYSICSENGINE_HPP

#include "../MPU6050-Library/abstractAccelerometer.hpp"
#include "particle.hpp"

/// @file

template <unsigned int N>
/// \brief
/// Abstract physics engine class
/// \details
/// This abstract class had all the necessary variables and functions for a basic 2D physics engine.
class physicsEngine {
 public:
  /// \brief Sensor where acceleration is based on.
  accelerometer_interface& accel;
  /// \brief Array of particles in physics engine.
  array<particle*, N> particles;
  /// \brief Vector of current acceleration in environment.
  vector acceleration = {0.0, 0.0};
  /// \brief The maximum acceleration possible in simulation.
  float max_acceleration;
  /// \brief Threshold before angle measurment is used to calculate acceleration.
  int accel_threshold;
  /// \brief Max speed of particles in simulation.
  float max_speed;
  /// \brief Used to calculate delta_time.
  uint64_t previous_time;
  /// \brief Resistance const calculated based on max_acceleration and max_speed.
  float resis_const;

 public:
  /// \brief
  /// Constructor abstract class
  /// \details
  /// This constructor should be called in the initializer list of the class that implements this abstract class.
  physicsEngine(accelerometer_interface& accel, const array<particle*, N>& particles, float max_accel,
                unsigned int accel_thresh, float max_speed)
      : accel(accel),
        particles(particles),
        max_acceleration(max_accel),
        accel_threshold(accel_thresh),
        max_speed(max_speed) {
    previous_time = now_us();
    resis_const = max_acceleration / (max_speed * max_speed);
  }

  /// \brief
  /// Abstract function update acceleration
  /// \details
  /// This function needs to be override in a class that implements this class.\n
  /// The function should update the acceleration based on the accel.
  virtual void updateAcceleration() = 0;

  /// \brief
  /// Abstract function draw acceleration
  /// \details
  /// This function needs to be override in a class that implements this class.\n
  /// The function should draw the particles in the choosen environment.
  virtual void drawParticles() = 0;

  /// \brief
  /// Update particles
  /// \details
  /// This function updates the speed and position of all the particles.\n
  /// First it update the speed of all the particles and then it will update the position.\n
  /// Call example: engine.updateParticles();
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
  /// Call example: engine.drawParticles();
  virtual void simulationLoop() {
    while (true) {
      updateAcceleration();
      updateParticles();
      drawParticles();
    }
  }
};

#endif