#include "Font11x15.h"

const uint8_t Font11x15::data11x15Start = '.';
const uint8_t Font11x15::data11x15End = 'm';

const uint8_t Font11x15::data11x15[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // space
    0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, //.
    0xFE, 0xFF, 0xFF, 0x07, 0x87, 0xC7, 0xE7, 0x77, 0xFF, 0xFF, 0xFE, 0x7E, 0xFE, 0xFE, 0xEE, 0xE6, 0xE2, 0xE0, 0xE0, 0xFE, 0xFE, 0x7E, // 0
    0x07, 0x07, 0x07, 0x07, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0xFE, 0xFE, 0xFE, 0xE0, 0xE0, 0xE0, 0xE0, // 1
    0x8E, 0xCF, 0xCF, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0xE2, 0xE2, 0xE2, 0xE2, 0xE2, 0xE2, 0xE2, 0xE0, // 2
    0x0E, 0x0F, 0x0F, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xFF, 0xFF, 0x7E, 0x70, 0xF0, 0xF0, 0xE2, 0xE2, 0xE2, 0xE2, 0xE2, 0xFE, 0xFE, 0x7E, // 3
    0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0xFE, 0xFE, 0xFE, // 4
    0xFF, 0xFF, 0xFF, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0x87, 0x72, 0xF2, 0xF2, 0xE2, 0xE2, 0xE2, 0xE2, 0xE2, 0xFE, 0xFE, 0x7E, // 5
    0xFE, 0xFF, 0xFF, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xCF, 0xCF, 0x8E, 0x7E, 0xFE, 0xFE, 0xE2, 0xE2, 0xE2, 0xE2, 0xE2, 0xFE, 0xFE, 0x7E, // 6
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE, // 7
    0x7E, 0xFF, 0xFF, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xFF, 0xFF, 0x7E, 0x7E, 0xFE, 0xFE, 0xE2, 0xE2, 0xE2, 0xE2, 0xE2, 0xFE, 0xFE, 0x7E, // 8
    0xFE, 0xFF, 0xFF, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xFF, 0xFF, 0xFE, 0x70, 0xF2, 0xF2, 0xE2, 0xE2, 0xE2, 0xE2, 0xE2, 0xFE, 0xFE, 0xFE, // 9
    0xFE, 0xFF, 0xFF, 0xC7, 0xC7, 0xC7, 0xC7, 0xC7, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFE, 0x02, 0x02, 0x02, 0x02, 0x02, 0xFE, 0xFE, 0xFE, // A
    0xFE, 0xFF, 0xFF, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0F, 0x0F, 0x0E, 0x7E, 0xFE, 0xFE, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xF0, 0xF0, 0x70, // C
    0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0x02, 0x02, 0x02, 0x02, 0x02, 0xFE, 0xFE, 0xFE, // H
    0xFF, 0xFF, 0xFF, 0x78, 0xF0, 0xE0, 0xF0, 0x78, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x02, 0x00, 0x00, 0xFE, 0xFE, 0xFE, // M
    0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x06, 0x0E, 0x1E, 0x3C, 0x78, 0xF0, 0x78, 0x3C, 0x1E, 0x0E, 0x06, // V
    0xFF, 0xFF, 0xFF, 0x00, 0x80, 0xC0, 0x80, 0x00, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0x1E, 0x0E, 0x06, 0x0E, 0x1E, 0xFE, 0xFE, 0xFE, // W
    0xFF, 0xFF, 0xFF, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE, // h
    0xF0, 0xF0, 0x70, 0x70, 0xF0, 0xE0, 0xF0, 0x70, 0x70, 0xF0, 0xF0, 0xFE, 0xFE, 0x00, 0x00, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0xFE, 0xFE, // m
};

const uint8_t* Font11x15::getCharData(char c){
  switch(c){
    case ' ':
      return Font11x15::data11x15;
    case '.':
      return Font11x15::data11x15 + 6;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return Font11x15::data11x15 + 12 + (c - '0') * 22;
    case 'A':
      return Font11x15::data11x15 + 12 + 10 * 22;
    case 'C':
      return Font11x15::data11x15 + 12 + 11 * 22;
    case 'H':
      return Font11x15::data11x15 + 12 + 12 * 22;
    case 'M':
      return Font11x15::data11x15 + 12 + 13 * 22;
    case 'V':
      return Font11x15::data11x15 + 12 + 14 * 22;
    case 'W':
      return Font11x15::data11x15 + 12 + 15 * 22;
    case 'h':
      return Font11x15::data11x15 + 12 + 16 * 22;
    case 'm':
      return Font11x15::data11x15 + 12 + 17 * 22;
    default:
      return Font11x15::data11x15;
  }
}

const uint8_t Font11x15::getCharWidth(char c){
  if(c < Font11x15::data11x15Start || c > Font11x15::data11x15End){
    // if out of bound return a .
    return 3;
  }

  switch(c){
    case ' ':
    case '.':
      return 3;
    default:
      return 11;
  }
}
