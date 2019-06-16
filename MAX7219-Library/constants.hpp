enum class MAX7219_register{
  no_op = 0x00,
  column7,
  column6,
  column5,
  column4,
  column3,
  column2,
  column1,
  column0,
  decode_mode,
  intensity,
  scan_limit,
  shutdown,
  display_test = 0x0F
};

// struct MAX7219Constants {
//   std::array<MAX7219_register, 8> columns = {MAX7219_register::column0, MAX7219_register::column1, MAX7219_register::column2, MAX7219_register::column3,
//                                      MAX7219_register::column4, MAX7219_register::column5, MAX7219_register::column6, MAX7219_register::column7};
// };
