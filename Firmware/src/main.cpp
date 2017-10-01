#include <Arduino.h>
#include <ClickEncoder.h>
#include <TimerOne.h>

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

ClickEncoder encoder(ENC_A, ENC_B, ENC_BTN, ENC_STEPS_PER_NOTCH);

uint32_t accumulatedmWh = 0; //accumulated milliWattHours
uint32_t accumulatedmAh = 0; //accumulated milliAmpereHours

uint32_t accumulatedmAmsec = 0; //accumulated milliAmpereMilliSeconds
uint32_t accumulatedmWmsec = 0; //accumulated milliWattMilliSeconds

uint16_t currentSet = 0; // current setpoint in mA

//which detail to show
// 0: Ampere
// 1: Watts
// 2: milli Amperehours
// 3: milli Watthours
uint8_t currentDetail = 2;

void timerIsr() {
  encoder.service();
}

void resetAccumulatedValues(){
  accumulatedmWh = 0;
  accumulatedmAh = 0;

  accumulatedmAmsec = 0;
  accumulatedmWmsec = 0;
}

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
  resetAccumulatedValues();

  display.clear();
}

void drawCurrent(uint32_t loadCurrent){
  String text = String(loadCurrent / 1000.f, 3) + " A";
  uint8_t textWidth = bigFont.getTextWidth(text);
  uint8_t startX = (OLED_WIDTH - textWidth) / 2;

  display.drawText(text, startX, 0, bigFont);
}

void drawPower(uint32_t loadPower){
  String text = String(loadPower / 1000.0f, 2) + " W";
  uint8_t textWidth = bigFont.getTextWidth(text);
  uint8_t startX = (OLED_WIDTH - textWidth) / 2;

  display.drawText(text, startX, 0, bigFont);
}

void drawmAh(uint32_t accumulatedmAh){
  String text;
  if(accumulatedmAh < 1000){
    text = String(accumulatedmAh) + " mAh";
  }else{
    text = String(accumulatedmAh / 1000.f, 2) + " Ah";
  }

  uint8_t textWidth = bigFont.getTextWidth(text);
  uint8_t startX = (OLED_WIDTH - textWidth) / 2;

  display.drawText(text, startX, 0, bigFont);
}

void drawmWh(uint32_t accumulatedmWh){
  String text;
  if(accumulatedmWh < 10000){
    text = String(accumulatedmWh / 1000.f, 2) + " Wh";
  }else{
    text = String(accumulatedmWh / 1000.f, 1) + " Wh";
  }

  uint8_t textWidth = bigFont.getTextWidth(text);
  uint8_t startX = (OLED_WIDTH - textWidth) / 2;

  display.drawText(text, startX, 0, bigFont);
}

void drawSecondaryInfo(uint32_t setCurrent, uint32_t loadCurrent, uint32_t loadVoltage, uint16_t temperature){
  uint8_t cellWidth = OLED_WIDTH / 3;

  //display the setpoint of the current on the left
  String cell1 = String(setCurrent / 1000.f, 2) + "A";
  display.drawText(cell1, 0, 3, smallFont);
  display.drawProgressbar((loadCurrent * 100) / I_MAX, 0, 2, (OLED_WIDTH / 3) - 1);

  //display the temperature centered on the screen
  String cell2 = String(temperature) + "nC";
  uint8_t startX = cellWidth + ((cellWidth - smallFont.getTextWidth(cell2)) / 2);
  display.drawText(cell2, startX, 3, smallFont);
  display.drawProgressbar((temperature * 100) / T_MAX, OLED_WIDTH / 3 * 1, 2, (OLED_WIDTH / 3) - 1);

  //display the current voltage right-aligned
  String cell3 = String(loadVoltage / 100.f, 2) + "V";
  uint8_t width = smallFont.getTextWidth(cell3);
  display.drawText(cell3, OLED_WIDTH - width, 3, smallFont);
  display.drawProgressbar((loadVoltage * 100) / U_MAX, OLED_WIDTH / 3 * 2, 2, (OLED_WIDTH / 3) - 1);
}

uint16_t measureVoltage(){
  //TODO: implement ADC reading
  static uint16_t base = 3500;
  //base += random(-10, 10);
  return base;
}

uint16_t measureCurrent(){
  //TODO: implement ADC reading
  return currentSet;
}

uint8_t measureTemperature(){
  //TODO: implement ADC reading
  static uint8_t base = 23;
  //base += random(-2, 2);
  return base;
}

void setCurrent(uint32_t current){

  if(current >= 0 && current <= I_MAX){
    currentSet = current;
    //TODO: set dac value apropriatley
  }
}

void handleHID() {
  int16_t encoderNewSteps = encoder.getValue();
  setCurrent(currentSet + (encoderNewSteps * 10));
  ClickEncoder::Button buttonState = encoder.getButton();
  switch (buttonState) {
    case ClickEncoder::Held:
      resetAccumulatedValues();
      break;
    case ClickEncoder::Clicked:
      currentDetail = (currentDetail + 1) % 4;
      break;
    default:
      break;
  }
}

void setup()   {
  display.begin();
  powerUp();
  display.clear();

  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);

  encoder.setAccelerationEnabled(true);

  Serial.begin(9600);
}

void loop() {
    static uint32_t lastUpdate = millis();

    uint32_t loadVoltage = measureVoltage(); // mV
    uint32_t loadCurrent = measureCurrent(); // mA
    uint8_t heatsinkTemperature = measureTemperature(); // °C
    uint32_t loadPower = (loadVoltage * loadCurrent) / 100; //mW
    uint32_t timeSinceLastUpdate = millis() - lastUpdate; // mS
    lastUpdate = millis();

    accumulatedmAmsec += loadCurrent * timeSinceLastUpdate;
    if(accumulatedmAmsec >= USEC_PER_HOUR){
      accumulatedmAh += 1;
      accumulatedmAmsec -= USEC_PER_HOUR;
    }

    accumulatedmWmsec += loadPower * timeSinceLastUpdate;
    if(accumulatedmWmsec >= USEC_PER_HOUR){
      accumulatedmWh += 1;
      accumulatedmWmsec -= USEC_PER_HOUR;
    }

    handleHID();

    display.clear();

    //draw primary info
    switch(currentDetail){
      case 0:
        drawCurrent(loadCurrent);
        break;
      case 1:
        drawPower(loadPower);
        break;
      case 2:
        drawmAh(accumulatedmAh);
        break;
      case 3:
        drawmWh(accumulatedmWh);
        break;
    }
    drawSecondaryInfo(currentSet, loadCurrent, loadVoltage, heatsinkTemperature);

    display.refresh();
}
