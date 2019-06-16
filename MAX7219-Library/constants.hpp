enum class MAX7219_register{
  no_op = 0x00,
  row7,
  row6,
  row5,
  row4,
  row3,
  row2,
  row1,
  row0,
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
