#include "../MAX7219-Library/MAX7219.hpp"
#include "../MAX7219-Library/windowDecorator.hpp"
#include "../MPU6050-Library/MPU6050.hpp"
#include "hwlib.hpp"

using hwlib::cout;
using hwlib::drawable;
using hwlib::endl;
using hwlib::window;
using hwlib::xy;
using std::array;
using std::max;

class xyDouble {
 public:
  double x;
  double y;

  xyDouble operator+(const xyDouble& rhs) const { return xyDouble{(x + rhs.x), (y + rhs.y)}; }
};

class particle : public drawable {
 private:
  xyDouble real_pos;  // deze variabele maken het mogelijk om een verfijndere positie te hebben
  xyDouble speed = {0.0, 0.0};
  xy size_environment;
  int x_max;
  int y_max;

 public:
  particle(const xy& start_pos, const xy& size_environment) : drawable(start_pos), size_environment(size_environment) {
    x_max = size_environment.x - 1;
    y_max = size_environment.y - 1;
    real_pos.x = start_pos.x;
    real_pos.y = start_pos.y;
  }

  void updateSpeed(const xyDouble& acceleration);
  void updatePosition();
  void draw(window& w) override;

  void userInput();
};

template <unsigned int N>
class simulation {
 private:
  hwlib::window& window;
  xy size;
  mpu6050::MPU6050& mpu;
  array<particle*, N> particles;
  xyDouble acceleration = {0.0, 0.0};
  double max_acceleration;
  int accel_threshold;

 public:
  simulation(hwlib::window& w, mpu6050::MPU6050& mpu, const array<particle*, N>& particles, double max_accel = 0.1,
             unsigned int accel_thresh = 10)
      : window(w),
        size(w.size),
        mpu(mpu),
        particles(particles),
        max_acceleration(max_accel),
        accel_threshold(accel_thresh) {}

  void updateAcceleration() {
    int angle_x = mpu.getAngleX();
    int angle_y = mpu.getAngleY();
    if (angle_x > accel_threshold || angle_x < -accel_threshold) {
      // cout << "above threshold X" << endl;
      acceleration.x = (max_acceleration * (angle_x / 90.0));
    } else {
      acceleration.x = 0;
    }
    if (angle_y > accel_threshold || angle_y < -accel_threshold) {
      // cout << "above threshold Y" << endl;
      acceleration.y = -1 * (max_acceleration * (angle_y / 90.0));
    } else {
      acceleration.y = 0;
    }

    // int acc_x_print = acceleration.x;
    // int acc_y_print = acceleration.y;
    // cout << "hoek X: " << angle_x << " Y: " << angle_y << endl;
    // cout << "acc X: " << acc_x_print << " Y: " << acc_y_print << endl;
  }

  void updateParticles() {
    for (unsigned int i = 0; i < N; i++) {
      particles[i]->updateSpeed(acceleration);
    }
    for (unsigned int i = 0; i < N; i++) {
      particles[i]->updatePosition();
    }
  }
  void drawParticles() {
    for (unsigned int i = 0; i < N; i++) {
      particles[i]->draw(window);
    }
    window.flush();
  }
};