#include "hwlib.hpp"

using hwlib::cout;
using hwlib::drawable;
using hwlib::endl;
using hwlib::window;
using hwlib::xy;
using std::array;
using std::max;

class particle : public drawable {
 private:
  xy size_environment;
  xy speed = xy(0, 0);
  int x_max;
  int y_max;

 public:
  particle(xy start_pos, xy size_environment) : drawable(start_pos), size_environment(size_environment) {
    x_max = size_environment.x - 1;
    y_max = size_environment.y - 1;
  }

  void updateSpeed(const xy& acceleration);
  void updatePosition();

  void userInput();
  void draw(window& w) override;
};

template <unsigned int N>
class simulation {
 private:
  window& window;
  xy size;
  MPU6050& mpu;
  array<particle*, N> particles;
  xy acceleration = xy(0, 0);

 public:
  simulation(window& w, MPU6050& mpu, const xy& size, const array<particle*, N>& particles)
      : window(w), size(size), mpu(mpu), particles(particles) {}

  void updateAcceleration();
  void updateParticles() {
    for (unsigned int i = 0; i < N; i++) {
      particles[i]->updateSpeed(acceleration);
    }
  }
  void drawParticles() {
    for (unsigned int i = 0; i < N; i++) {
      particles[i]->draw(window);
    }
    window.flush();
  }
};