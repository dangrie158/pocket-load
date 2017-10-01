#ifndef BITMAP_H_
#define BITMAP_H_

#include <avr/pgmspace.h>
#include <inttypes.h>

class Bitmap {
  public:

    explicit Bitmap(const uint8_t *bitmapData, uint8_t width, uint8_t height)
        : data(bitmapData), width(width), height(height){};

    inline const uint8_t getPageBlock(uint8_t x, uint8_t page) const {
      return pgm_read_byte(data + (x + (page * this->width)));
    }

    const uint8_t *data;
    uint8_t width;
    uint8_t height;
};
#endif // BITMAP_H_
