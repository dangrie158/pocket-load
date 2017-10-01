#include "SSD1306.h"
#include <Arduino.h>

SSD1306::SSD1306() {
  memset(buffer, OLED_BUFFER_SIZE, 0);
}

void SSD1306::setPixel(int16_t x, int16_t y) {
  uint16_t idx = x + (y / 8) * OLED_WIDTH;
  uint8_t bit = y % 8;

  buffer[idx] |= (1 << bit);
}

void SSD1306::clearPixel(int16_t x, int16_t y) {
  uint16_t idx = x + (y / 8) * OLED_WIDTH;
  uint8_t bit = y % 8;

  buffer[idx] &= ~(1 << bit);
}

void SSD1306::setPage(int16_t x, uint8_t page, uint8_t data){
  uint16_t idx = x + page * OLED_WIDTH;
  buffer[idx] = data;
}

void SSD1306::drawText(const String& text, int16_t x, uint8_t page, Font& font){
  for(uint8_t i = 0; i < text.length(); i++){
    uint8_t c = text.charAt(i);
    const uint8_t* data = font.getCharData(c);
    uint8_t charWidth = font.getCharWidth(c);
    uint8_t fontPages = (font.height / 8) + 1;

    //draw the character
    for(uint8_t col = 0; col < charWidth; col++){
      for(uint8_t curPage = page; curPage < page + fontPages; curPage++){
        uint8_t pageData = pgm_read_byte(data + col + (curPage - page) * charWidth);
        if((curPage - page) > 0){
          pageData >>= 1;
        }
        this->setPage(x + col, curPage, pageData);
      }
    }

    //go to the next character
    x += charWidth + 1;
  }
}

void SSD1306::drawProgressbar(const uint8_t percent, int16_t x, uint8_t page, uint8_t width){
  uint8_t i = 0;
  uint8_t filledCols = ((width - 3) * percent) / 100;
  this->setPage(x + i++, page, 0x7E);
  this->setPage(x + i++, page, 0x42);
  for(; i < width - 2; i++){
    if(i <= filledCols){
      this->setPage(x + i, page, 0x5A);
    }else{
      this->setPage(x + i, page, 0x42);
    }
  }
  this->setPage(x + i++, page, 0x42);
  this->setPage(x + i++, page, 0x7E);
}

void SSD1306::drawBitmap(const Bitmap& bitmap, int16_t x, uint8_t page){
  for(uint8_t j = 0; j < bitmap.height / 8; j++){
    for(uint8_t i = 0; i < bitmap.width; i++){
      this->setPage(i + x, j + page, bitmap.getPageBlock(i, j));
    }
  }
}

void SSD1306::refresh() {
  sendcommand(SSD1306_COLUMNADDR);
  sendcommand(0); // start at column == 0
  sendcommand(OLED_WIDTH - 1); // end at column == 127

  sendcommand(SSD1306_PAGEADDR);
  sendcommand(0); // start at page == 0
  sendcommand(7); // end at page == 7

  // we can go by 16s
  for(uint16_t ii = 0; ii < OLED_BUFFER_SIZE; ii+=16) {
    Wire.beginTransmission(OLED_address);
    Wire.write(0x40);

    for(uint16_t jj = 0; jj < 16; ++jj) {
      Wire.write(buffer[ii + jj]);
    }

    Wire.endTransmission();
  }
}

void SSD1306::begin() {
  Wire.begin();
  init_OLED();
  reset();
  clear();
}

//==========================================================//
// Resets display depending on the actual mode.
void SSD1306::reset(void)
{
  shutdown();
  clear();
  powerOn();
}

//==========================================================//
// Turns display on.
void SSD1306::powerOn(void)
{
  sendcommand(0xaf);        //display on
}

//==========================================================//
// Turns display off.
void SSD1306::shutdown(void)
{
  sendcommand(0xae);    //display off
}

//==========================================================//
// Clears the display by sendind 0 to all the screen map.
void SSD1306::clear(void)
{
  memset(buffer, 0, OLED_BUFFER_SIZE);
}

//==========================================================//
// Used to send commands to the display.
void SSD1306::sendcommand(unsigned char com)
{
  Wire.beginTransmission(OLED_address);     //begin transmitting
  Wire.write(0x80);                          //command mode
  Wire.write(com);
  Wire.endTransmission();                    // stop transmitting
}

//==========================================================//
// Inits oled and draws logo at startup
void SSD1306::init_OLED(void)
{
  sendcommand(0xae);    //display off
  sendcommand(0xa6);            //Set Normal Display (default)

  // Adafruit Init sequence for 128x64 OLED module
  sendcommand(0xAE);             //DISPLAYOFF
  sendcommand(0xD5);            //SETDISPLAYCLOCKDIV
  sendcommand(0x80);            // the suggested ratio 0x80
  sendcommand(0xA8);            //SSD1306_SETMULTIPLEX
  sendcommand(0x3F);
  sendcommand(0xD3);            //SETDISPLAYOFFSET
  sendcommand(0x0);             //no offset
  sendcommand(0x40 | 0x0);      //SETSTARTLINE
  sendcommand(0x8D);            //CHARGEPUMP
  sendcommand(0x14);
  sendcommand(0x20);             //MEMORYMODE
  sendcommand(0x00);             //0x0 act like ks0108

  //sendcommand(0xA0 | 0x1);      //SEGREMAP   //Rotate screen 180 deg
  sendcommand(0xA0);

  //sendcommand(0xC8);            //COMSCANDEC  Rotate screen 180 Deg
  sendcommand(0xC0);

  sendcommand(0xDA);            //0xDA
  sendcommand(0x12);           //COMSCANDEC
  sendcommand(0x81);           //SETCONTRAS
  sendcommand(0xCF);           //
  sendcommand(0xd9);          //SETPRECHARGE
  sendcommand(0xF1);
  sendcommand(0xDB);        //SETVCOMDETECT
  sendcommand(0x40);
  sendcommand(0xA4);        //DISPLAYALLON_RESUME
  sendcommand(0xA6);        //NORMALDISPLAY

  clear();
  sendcommand(0x2e);            // stop scroll
  //----------------------------REVERSE comments----------------------------//
  sendcommand(0xa0);    //seg re-map 0->127(default)
  sendcommand(0xa1);    //seg re-map 127->0
  sendcommand(0xc8);
  delay(1000);
  //----------------------------REVERSE comments----------------------------//
  // sendcommand(0xa7);  //Set Inverse Display
  // sendcommand(0xae);   //display off
  sendcommand(0x20);            //Set Memory Addressing Mode
  sendcommand(0x00);            //Set Memory Addressing Mode ab Horizontal addressing mode
  //  sendcommand(0x02);         // Set Memory Addressing Mode ab Page addressing mode(RESET)

  sendcommand(SSD1306_SETCONTRAST);
  sendcommand(0xff);
}
