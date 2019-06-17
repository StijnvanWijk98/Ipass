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
