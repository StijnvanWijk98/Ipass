#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "abstractPhysicsEngine.hpp"
#include "particle.hpp"

/// @file

template <unsigned int N>
class simulator : public physicsEngine<N> {
 private:
  hwlib::window& window;  // Window where particles will be draw on.

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
  simulator(hwlib::window& w, MPU6050& mpu, const array<particle*, N>& particles, float max_accel = 30,
            unsigned int accel_thresh = 10, float max_speed = 8)
      : physicsEngine<N>(mpu, particles, max_accel, accel_thresh, max_speed), window(w) {}

  /// \brief
  /// Update acceleration
  /// \details
  /// This function updates the acceleration of the simulation.\n
  /// If the angle given by the MPU6050 is above the threshold, than it calculates the acceleration.\n
  /// The acceleration is never greater than max_acceleration.\n
  /// Call example: simu.updateAcceleration();
  void updateAcceleration() override {
    int angle_x = accel.getAngleX();
    int angle_y = accel.getAngleY();
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
  void updateParticles() override {
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
  void drawParticles() override {
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
  //   void simulationLoop() {
  //     while (true) {
  //       updateAcceleration();
  //       updateParticles();
  //       drawParticles();
  //     }
  //   }
};

#endif