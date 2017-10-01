#include <avr/pgmspace.h>
#include "Font.h"

#ifndef _11X15_H
#define _11X15_H

class Font11x15: public Font{
  public:
    Font11x15() : Font(15){}
    virtual const uint8_t* getCharData(char c);
    virtual const uint8_t getCharWidth(char c);

  private:
    static const uint8_t data11x15[] PROGMEM;
    static const uint16_t data11x15StartAddr[] PROGMEM;
    static const uint8_t data11x15Start;
    static const uint8_t data11x15End;
};

#endif
