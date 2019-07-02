#include "../MAX7219-Library/MAX7219.hpp"
#include "../MAX7219-Library/windowDecorator.hpp"
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

class xyFloat {
 public:
  float x;
  float y;

  xyFloat operator+(const xyFloat& rhs) const { return xyFloat{(x + rhs.x), (y + rhs.y)}; }

  xyFloat& operator*=(const int& rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
  }
  xyFloat operator*(const xyFloat& rhs) const { return xyFloat{x * rhs.x, y * rhs.y}; }

  friend xyFloat operator*(const float& lhs, const xyFloat& rhs) { return xyFloat{lhs * rhs.x, lhs * rhs.y}; }

  xyFloat operator*(const float& rhs) const { return xyFloat{x * rhs, y * rhs}; }

  friend hwlib::ostream& operator<<(hwlib::ostream& lhs, const xyFloat& rhs) {
    int x_base = rhs.x;
    int y_base = rhs.y;
    int x_dec = abs((rhs.x - x_base) * 1e6);
    int y_dec = abs((rhs.y - y_base) * 1e6);
    lhs << '(' << x_base << '.' << x_dec << ',' << y_base << '.' << y_dec << ')';
    return lhs;
  }

  float magnitude() { return sqrt((x * x) + (y * y)); }
  float squaredMagnitude() { return ((x * x) + (y * y)); }

  xyFloat norm() {
    float eps = 0.001;
    float mag = magnitude();
    if (mag < eps) mag = eps;
    return *this * (1 / magnitude());
  }
};

class particle : public drawable {
 private:
  xyFloat speed = {0.0, 0.0};
  xyFloat real_pos;  // deze variabele maken het mogelijk om een verfijndere positie te hebben

  int x_max;
  int y_max;
  float d_max;  // Distance from corner to the middle op the window
  float radius = 0.5;

 public:
  particle(const xy& start_pos, const xy& size_environment) : drawable(start_pos) {
    x_max = size_environment.x;
    y_max = size_environment.y;
    real_pos.x = start_pos.x;
    real_pos.y = start_pos.y;
    d_max = (0.25 * x_max * x_max) + (0.25 * y_max * y_max);
  }

  void updateSpeed(const xyFloat& acceleration, const double& delta_time, const float& resistance_const);
  void draw(window& w) override;
  xyFloat getRealPos() { return real_pos; }
  void multiplySpeed(int i) { speed *= i; }

  template <unsigned int N>
  void updatePosition(const double& delta_time, const array<particle*, N>& particles, unsigned int id) {
    // cout << "1real_pos: " << real_pos << "\n"; 
    float new_x = real_pos.x + (speed.x * delta_time);
    float new_y = real_pos.y + (speed.y * delta_time);
    // xyFloat news{new_x, new_y};
    // cout << "speed: " << speed << "\n";
    // cout << "2new_pos:  " << news << "\n";
    // Collision
    for (unsigned int i = id + 1; i < N; i++) {
      xyFloat pos_comp = particles[i]->getRealPos();
      float distance = ((pos_comp.x - real_pos.x) * (pos_comp.x - real_pos.x)) +
                       ((pos_comp.y - real_pos.y) * (pos_comp.y - real_pos.y));
      if (distance < 1) {  // This is the radius+radius squared
        // cout << "collision detected\n";
        new_x = real_pos.x;
        new_y = real_pos.y;
        speed = {0.0, 0.0};
        // particles[i]->multiplySpeed(-1);
        break;
      }
    }
    if (new_x > x_max - radius) {
      new_x = x_max - radius;
      speed.x = 0;
    } else if (new_x < 0 + radius) {
      new_x = 0 + radius;
      speed.x = 0;
    }
    if (new_y > y_max - radius) {
      new_y = y_max - radius;
      speed.y = 0;
    } else if (new_y < 0 + radius) {
      new_y = 0 + radius;
      speed.y = 0;
    }
    real_pos.x = new_x;
    real_pos.y = new_y;
    // cout << "3real_pos: " << real_pos << "\n";
  }
};

template <unsigned int N>
class simulation {
 private:
  hwlib::window& window;
  xy size;
  mpu6050::MPU6050& mpu;
  array<particle*, N> particles;
  xyFloat acceleration = {0.0, 0.0};
  float max_acceleration;
  int accel_threshold;
  float max_speed;
  uint64_t previous_time;
  float resistance_const;

 public:
  simulation(hwlib::window& w, mpu6050::MPU6050& mpu, const array<particle*, N>& particles, float max_accel = 30,
             unsigned int accel_thresh = 10, float max_speed = 8)
      : window(w),
        size(w.size),
        mpu(mpu),
        particles(particles),
        max_acceleration(max_accel),
        accel_threshold(accel_thresh),
        max_speed(max_speed) {
    previous_time = now_us();
    resistance_const = max_acceleration / (max_speed * max_speed);
  }

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

    // int acc_x_print = acceleration.x;
    // int acc_y_print = acceleration.y;
    // cout << "hoek X: " << angle_x << " Y: " << angle_y << endl;
    // cout << "acc X: " << acc_x_print << " Y: " << acc_y_print << endl;
  }

  void updateParticles() {
    uint64_t current_time = now_us();
    double d_time = (current_time - previous_time) / 1e6;
    // cout << "time diff: " << (current_time - previous_time) << "\n";
    previous_time = current_time;
    for (unsigned int i = 0; i < N; i++) {
      particles[i]->updateSpeed(acceleration, d_time, resistance_const);
    }
    for (unsigned int i = 0; i < N; i++) {
      particles[i]->updatePosition(d_time, particles, i);
    }
  }
  void drawParticles() {
    for (unsigned int i = 0; i < N; i++) {
      particles[i]->draw(window);
    }
    window.flush();
  }
};