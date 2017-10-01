#include <avr/pgmspace.h>
#include "Font.h"

#ifndef _5X7_H
#define _5X7_H

class Font5x7: public Font{
  public:
    Font5x7() : Font(7){}
    virtual const uint8_t* getCharData(char c);
    virtual const uint8_t getCharWidth(char c);

  private:
    static const uint8_t data5x7[] PROGMEM;
    static const uint8_t data5x7StartAddr[] PROGMEM;
    static const uint8_t data5x7Start;
    static const uint8_t data5x7End;
};

#endif
