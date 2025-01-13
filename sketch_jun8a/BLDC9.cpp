#include "BLDC9.h"

#include <Wire.h>
#include <lvgl.h>
#include "ui.h"

ExEEPROM eeprom_data;

bool toggleOnOff[8] = {false};
int speed[8] = {0};
int slider[8] = {0};

struct BLDC_DATA
{
  int speed;
  bool onOff;
};

void BLDC9::begin(Servo &BLDC, int pin)
{
  Serial.begin(115200);

  BLDC.setPeriodHertz(50);
  BLDC.attach(pin, 1000, 2000);

  // return;
}

BLDC9::BLDC_DATA BLDC9::getData(int speed, int onOff)
{
  BLDC_DATA bldctest = {speed, onOff};
  return bldctest;
}
void BLDC9::setSpeed(Servo &BLDC, int slider_value, int bldcIndex)
{    // speed[bldcIndex] = map(slider_value, 0, 100, 13, 200);
  speed[bldcIndex] = map(slider_value, 0, 100, 0, 100);
  
  // BLDC.write(speed[bldcIndex]);
  
}

void BLDC9::setOff(Servo &BLDC, int bldcIndex, int addr)
{
    // BLDC9::setSpeed(BLDC, 0, bldcIndex);
    speed[bldcIndex] = 0;
    // BLDC.write(62);   
    eeprom_data.write(addr, 0);
    toggleOnOff[bldcIndex] = false;
  // if (speed[bldcIndex] > 0)
  // {
  // }

  Serial.println("off");
}

void BLDC9::setOn(Servo &BLDC, int bldcIndex)
{ 
  // if (speed[bldcIndex] > 0)
  // {
  //   /* code */
  // }

  // if (speed[bldcIndex] == 0){
  //   BLDC.write(0);
  // }
  
  // // BLDC9::setSpeed(BLDC, speed[bldcIndex], bldcIndex);
  speed[bldcIndex] = speed[bldcIndex];
  // BLDC.write(speed[bldcIndex]);
  toggleOnOff[bldcIndex] = true;
  Serial.println("on");
}

void BLDC9::writeBLDC(int addr, BLDC_DATA data)
{
  Wire.beginTransmission(0x50);
  Wire.write((int)(addr >> 8));
  Wire.write((int)(addr & 0xFF));
  Wire.write(data.onOff);
  Wire.write(data.speed);
  Wire.endTransmission();
  delay(5);
}

BLDC9::BLDC_DATA BLDC9::readBLDC(int addr)
{
  BLDC_DATA data;
  Wire.beginTransmission(0x50);
  Wire.write((int)(addr >> 8));
  Wire.write((int)(addr & 0xFF));
  Wire.endTransmission();
  Wire.requestFrom(0x50, 4);
  if (Wire.available())
  {
    data.onOff = Wire.read();
    data.speed = Wire.read();
  }

  return data;
}
