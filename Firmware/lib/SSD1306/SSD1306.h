#ifndef SSD1306_H
#define SSD1306_H

#include <Wire.h>
#include "Font.h"
#include "Bitmap.h"

#define OLED_address  0x3c
#define OLED_WIDTH 96
#define OLED_HEIGHT 32
#define OLED_BUFFER_SIZE (OLED_WIDTH * OLED_HEIGHT / 8)

#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22
#define SSD1306_SETCONTRAST 0x81

class SSD1306 {
  public:
    SSD1306();

    void setPixel(int16_t x, int16_t y);
    void clearPixel(int16_t x, int16_t y);
    void setPage(int16_t x, uint8_t page, uint8_t data);
    void drawText(const String& text, int16_t x, uint8_t page, Font& font);
    void drawProgressbar(const uint8_t percent, int16_t x, uint8_t page, uint8_t width);
    void drawBitmap(const Bitmap& bitmap, int16_t x, uint8_t page);
    void refresh();
    void begin();
    void reset(void);
    void powerOn(void);
    void shutdown(void);
    void clear(void);
    void sendcommand(unsigned char com);

  private:
    uint8_t buffer[OLED_BUFFER_SIZE];
    void init_OLED(void);
};

#endif
