#ifndef FONT_H
#define FONT_H

#include <inttypes.h>
#include <Arduino.h>

class Font {
  public:
    Font(uint8_t height): height(height){}
    virtual const uint8_t* getCharData(char c) = 0;
    virtual const uint8_t getCharWidth(char c) = 0;

    inline uint8_t getTextWidth(const String& text){
      uint8_t textWidth = 0;

      for(uint8_t i = 0; i < text.length(); i++){
        textWidth += this->getCharWidth(text.charAt(i)) + 1;
      }

      return textWidth;
    }

    const uint8_t height;
};

#endif
