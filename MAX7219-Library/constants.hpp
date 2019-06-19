enum class MAX7219_register {
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

enum class MAX7219_commands {
  display_normal = 0x00,
  display_test = 0x01,
  decode_none = 0x00,
  shutdown_normal = 0x01,
  scan_limit_max = 0x07,
  intensity_base = 0x05,
  no_op = 0x00
};