#ifndef BLDC9_H
#define BLDC9_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include "ExEEPROM.h"

extern bool toggleOnOff[8];
extern int speed[8];
extern int slider[8];

class BLDC9
{
private:
public:
  struct BLDC_DATA
  {
    int speed;
    bool onOff;
  };

  void begin(Servo &BLDC, int pin);
  void setSpeed(Servo &BLDC, int slider, int index);
  void setOff(Servo &BLDC, int index, int addr);
  void setOn(Servo &BLDC, int index);
  void writeBLDC(int addr, BLDC_DATA data);
  BLDC_DATA getData(int speed, int onOff);
  BLDC_DATA readBLDC(int addr);
};

#endif