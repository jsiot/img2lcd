#include <LCD4884.h>

unsigned char img[] = {
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x07,0x03,0x00,0x20,0x50,0xaa,0x7f,0xaa,0xff,0xaa,0xff,0xaa,0xff,0xaa,0xff,0xaa,0xff,0xaa,0xff,0xaa,0xff,0xaa,0x7f,0x2a,0x7f,0x2a,0x1f,0x0a,0x9f,0x8a,0x8f,0x8a,0x9f,0x8a,0x1f,0x2a,0x7f,0x2a,0xff,0xaa,0xff,0xaa,0xff,0xa8,0xf8,0xa1,0xc3,0x8f,0x0f,0x1f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfc,0xa0,0x00,0x00,0x00,0x28,0x11,0x2a,0x17,0x2a,0x5f,0x2a,0x7f,0x2a,0x3f,0x0a,0x1f,0x42,0x07,0x20,0x11,0x80,0xc4,0xc0,0xf0,0xf0,0xf9,0xf9,0xf9,0xf9,0xf9,0xf3,0xf3,0xc7,0xc7,0x0e,0x3e,0x3c,0xf8,0xf8,0xc3,0xc2,0x07,0x0a,0x3f,0xaa,0xff,0xaa,0xff,0xaa,0xfc,0xa8,0xe1,0x83,0x0f,0x1f,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfc,0x38,0x00,0x02,0x85,0x22,0x01,0x00,0x88,0x80,0xc3,0x81,0xc0,0xc0,0xc0,0x80,0x00,0x7f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf9,0xf0,0x70,0x3b,0x1f,0x82,0xc0,0xe0,0xff,0xff,0xff,0x7f,0x7f,0x1e,0x18,0x80,0xc1,0xaa,0xff,0xaa,0xff,0xaa,0xff,0xaa,0xff,0xaa,0xfe,0xa8,0xf0,0xa3,0x87,0x8f,0x1f,0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xbf,0x1f,0x0f,0x43,0x20,0x10,0x08,0x00,0x00,0x00,0xb8,0xfc,0xfe,0xff,0xff,0xff,0x3f,0x1f,0x0f,0x1f,0xff,0xfe,0xf8,0xf8,0xf1,0x33,0x33,0x03,0x83,0xc3,0xe3,0xf1,0xf8,0x7c,0x3e,0x1f,0x8f,0xcf,0x87,0xe3,0xa3,0xf0,0xa8,0xfc,0x2a,0x3f,0x2a,0x1f,0x8a,0xcf,0xca,0x47,0x22,0x07,0x02,0x07,0x02,0x47,0xca,0xcf,0x0a,0x3f,0x2a,0xfc,0xa8,0xf0,0xa0,0x43,0x0f,0x0f,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0f,0x0f,0x0f,0x1e,0x0e,0x0f,0x87,0x47,0xa1,0xd1,0xa8,0x7e,0x2e,0x17,0x0b,0x47,0x03,0x41,0x88,0x5c,0xaa,0x7f,0x2a,0x3f,0x0a,0x87,0xc2,0x41,0x00,0x19,0x0c,0x06,0xe2,0xf2,0xf8,0xf8,0xf0,0x06,0x06,0x0f,0x0f,0x47,0xe6,0xe0,0x39,0x31,0x04,0x04,0x80,0x17,0x0a,0x01,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf8,0xf0,0xe0,0xe0,0xe0,0xc4,0x88,0x80,0x80,0x90,0x80,0x80,0x80,0xc0,0xc0,0xc4,0xe2,0xe3,0xe2,0xe1,0xe0,0xf1,0xe0,0xf0,0xe0,0xc0,0x82,0x11,0x00,0x01,0x08,0x15,0x80,0x80,0x80,0xc0,0xe0,0xe1,0x80,0x1c,0x3e,0x1f,0x0e,0x8c,0xe0,0xe1,0x60,0x04,0x0c,0x9f,0x8f,0x03,0x22,0x10,0x28,0x1c,0x28,0x1e,0x2a,0x07,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


void setup() {
  lcd.LCD_init();
  lcd.LCD_clear();
  lcd.backlight(ON);
}

void loop() { 
  lcd.LCD_draw_bmp_pixel(0,0, img, 84,48);
}



