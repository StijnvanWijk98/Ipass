#include "hwlib.hpp"

enum class testing { a = 0, b, c, d };

enum class Register {
  no_op = 0x00,
  digit0,
  digit1,
  digit2,
  digit3,
  digit4,
  digit5,
  digit6,
  digit7,
  decode_mode,
  intensity,
  scan_limit,
  shutdown,
  display_test = 0x0F
};

enum class Commands {};

enum class CMD_Displaytest { display_normal = 0x00, display_test = 0x01 };
enum class CMD_Shutdown { shutdown_shutdown = 0x00, shutdown_normal = 0x01 };
enum class CMD_Decode { no_decode = 0x00, all_decode = 0xFF };
enum class CMD_Digit { column0 = 0x00, column1, column2, column3, column4, column5, column6, column7 };

void printUint16(uint16_t to_print) {
  for (int i = 15; i >= 0; i--) {
    hwlib::cout << "i:" << i << '-' << (to_print & (1 << i)) << hwlib::endl;
  }
}

uint16_t addTwoInt(Register reg_adr, uint8_t right_side) {
  uint8_t left_side = static_cast<uint8_t>(reg_adr);
  uint16_t ret_value = left_side;
  ret_value = ret_value << 8;
  ret_value |= right_side;
  printUint16(ret_value);
  return ret_value;
}

void sendData(const uint16_t& data) {
  namespace target = hwlib::target;
  auto clk = target::pin_out(target::pins::d10);
  auto dout = target::pin_out(target::pins::d8);
  auto load = target::pin_out(target::pins::d9);

  int clock_time = 100;

  load.write(0);
  load.flush();
  hwlib::wait_ns(50);
  for (int_fast8_t shift = 16; shift >= 0; shift--) {
    uint16_t write_data = data & (1 << shift);
    // hwlib::cout << write_data << hwlib::endl;
    dout.write(write_data);
    dout.flush();
    hwlib::wait_ns(clock_time);
    clk.write(1);
    clk.flush();
    hwlib::wait_ns(clock_time);
    clk.write(0);
    clk.flush();
  }
  load.write(1);
  load.flush();
}

int main() {
  hwlib::wait_ms(500);
  hwlib::cout << "This is a test\n";
  addTwoInt(Register::intensity, 0x03);

  // uint16_t screen_normal = 0x0F00;
  // uint16_t screen_test = 0x0F01;

  // for (;;) {
  //   sendData(screen_test);
  //   hwlib::wait_ms(5000);
  //   sendData(screen_normal);
  //   hwlib::wait_ms(5000);
  // }
  return 0;
}

// hwlib::cout << "hallo dit is test" << hwlib::endl;
// testing a = testing::a;
// switch (a) {
//   case testing::a: hwlib::cout << 'a' << hwlib::endl; break;
//   case testing::b: hwlib::cout << 'b' << hwlib::endl; break;
//   case testing::c: hwlib::cout << 'c' << hwlib::endl; break;
//   case testing::d: hwlib::cout << 'd' << hwlib::endl; break;
// }