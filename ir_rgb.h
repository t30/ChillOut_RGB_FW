//Remote Button layout
//
//
//  00  01  02  03    ##  Lup    Ldn    Lof    Lon
//  04  05  06  07    ##  Red    Gre    Blu    Whi
//  08  09  10  11    ##  XXX    XXX    XXX    fls
//  12  13  14  15    ##  XXX    XXX    XXX    str
//  16  17  18  19    ##  XXX    XXX    XXX    fad
//  20  21  22  23    ##  XXX    XXX    XXX    smt
//
unsigned int myBtn[24][6] = {
  {0x90, 0x6f, 0x00, 0x00, 0x00, 0x00},
  {0xb8, 0x47, 0x01, 0x00, 0x00, 0x01},
  {0xf8, 0x07, 0x02, 0x00, 0x00, 0x02},
  {0xb0, 0x4f, 0x03, 0x00, 0x00, 0x03},

  {0x98, 0x67, 0xff, 0x00, 0x00, 0x04},
  {0xd8, 0x27, 0x00, 0xff, 0x00, 0x05},
  {0x88, 0x77, 0x00, 0x00, 0xff, 0x06},
  {0xa8, 0x57, 0xff, 0xff, 0xff, 0x07},

  {0xe8, 0x17, 0xff, 0x40, 0x00, 0x08},
  {0x48, 0xb7, 0x00, 0xff, 0x40, 0x09},
  {0x68, 0x97, 0x40, 0x00, 0xff, 0x0a},
  {0xb2, 0x4d, 0x00, 0x00, 0x00, 0x0b},

  {0x02, 0xfd, 0xff, 0x80, 0x00, 0x0c},
  {0x32, 0xcd, 0x00, 0xff, 0x80, 0x0d},
  {0x20, 0xdf, 0x80, 0x00, 0xff, 0x0e},
  {0x00, 0xff, 0x00, 0x00, 0x00, 0x0f},

  {0x50, 0xaf, 0xff, 0xc0, 0x00, 0x10},
  {0x78, 0x87, 0x00, 0xff, 0xc0, 0x11},
  {0x70, 0x8f, 0xc0, 0x00, 0xff, 0x12},
  {0x58, 0xa7, 0x00, 0x00, 0x00, 0x13},

  {0x38, 0xc7, 0xff, 0xff, 0x00, 0x14},
  {0x28, 0xd7, 0x00, 0xff, 0xff, 0x15},
  {0xf0, 0x0f, 0xff, 0x00, 0xff, 0x16},
  {0x30, 0xcf, 0x00, 0x00, 0x00, 0x17}};
