#include <Arduino.h>

#include "MCP4921.h"
#include "SSD1306.h"
#include "Font5x7.h"
#include "Font11x15.h"

#include "definitions.h"
#include "bitmaps.h"

SSD1306 display;
Font5x7 smallFont;
Font11x15 bigFont;

MCP4921 dac(MCP4921_CS);

void shutdown(){
  display.shutdown();
  dac.shutdown();
}

void powerUp(){
  display.reset();
  display.drawBitmap(nupoLogo, 16, 0);
  display.refresh();
  delay(1000);

  dac.wakeup();
}



void drawPrimaryInfo(const String& text){
  uint8_t textWidth = bigFont.getTextWidth(text);
  uint8_t startX = (OLED_WIDTH - textWidth) / 2;

  display.drawText(text, startX, 0, bigFont);
}

void drawSecondaryInfo(uint32_t setCurrent, uint32_t loadCurrent, uint32_t loadVoltage, uint16_t temperature){
  uint8_t cellWidth = OLED_WIDTH / 3;

  String cell1 = String(setCurrent / 1000.f, 2) + "A";
  display.drawText(cell1, 0, 3, smallFont);
  display.drawProgressbar((loadCurrent * 100) / I_MAX, 0, 2, (OLED_WIDTH / 3) - 1);

  String cell2 = String(temperature) + "nC";
  uint8_t startX = cellWidth + ((cellWidth - smallFont.getTextWidth(cell2)) / 2);
  display.drawText(cell2, startX, 3, smallFont);
  display.drawProgressbar((temperature * 100) / T_MAX, OLED_WIDTH / 3 * 1, 2, (OLED_WIDTH / 3) - 1);


  String cell3 = String(loadVoltage / 100.f, 2) + "V";
  uint8_t width = smallFont.getTextWidth(cell3);
  display.drawText(cell3, OLED_WIDTH - width, 3, smallFont);
  display.drawProgressbar((loadVoltage * 100) / U_MAX, OLED_WIDTH / 3 * 2, 2, (OLED_WIDTH / 3) - 1);
}

void setup()   {
  Serial.begin(9600);

  display.begin();
  powerUp();
  display.clear();

  drawPrimaryInfo("5.123 A");
  drawSecondaryInfo(2000, 4000, 2342, 45);

  display.refresh();
}


void loop() {

}
