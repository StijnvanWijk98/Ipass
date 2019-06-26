#include "hwlib.hpp"

using hwlib::cout;
using hwlib::drawable;
using hwlib::endl;
using hwlib::xy;
using std::max;

class particle : public drawable {
 private:
  xy size_enviroment;
  xy acceleration = xy(0,0);

 public:
  particle(xy start_pos, xy size_enviroment) : drawable(start_pos), size_enviroment(size_enviroment) {}

  void update();

  void userInput();
};