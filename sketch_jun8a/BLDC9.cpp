#include <Wire.h>
#include <lvgl.h>
#include <Arduino.h>
#include <ESP32Servo.h>
#include "ui.h"
#include "BLDC9.h"

bool toggleOnOff[8] = {false};
int speed[8] = {0};
int stateDirection[8] = {1};
int slider[8] = {0};

struct data_bldc
{
  int speed;
  bool onOff;
  int direction;
};

void BLDC9::begin(Servo &BLDC, int pin)
{
  Serial.begin(115200);

  BLDC.setPeriodHertz(50);
  BLDC.attach(pin, 1000, 2000);

  return;
}

BLDC9::data_bldc BLDC9::getData(int speed, int onOff, int direction)
{
  data_bldc bldctest = {speed, onOff, direction};
  return bldctest;
}
void BLDC9::setSpeed(Servo &BLDC, int slider_value, int bldcIndex)
{
  stateDirection[bldcIndex] = setStateDirection(bldcIndex);
  if (stateDirection[bldcIndex] == 0)
  {
    speed[bldcIndex] = map(slider_value, 0, 100, 93, 62);
    // getStateDirection(1, bldcIndex);
  }

  if (stateDirection[bldcIndex] == 1)
  {
    speed[bldcIndex] = map(slider_value, 0, 100, 95, 125);
    // getStateDirection(0, bldcIndex);
  }

  BLDC.write(speed[bldcIndex]);
}

void BLDC9::setOff(Servo &BLDC, int bldcIndex)
{
  if (((stateDirection[bldcIndex] == 0) && speed[bldcIndex]) > 0)
  {
    BLDC.write(93);
    toggleOnOff[bldcIndex] = false;
  }

  if (((stateDirection[bldcIndex] == 1) && speed[bldcIndex]) > 0)
  {
    BLDC.write(95);
    toggleOnOff[bldcIndex] = false;
  }
  Serial.println("off");
}

void BLDC9::setOn(Servo &BLDC, int bldcIndex)
{
  BLDC.write(speed[bldcIndex]);

  toggleOnOff[bldcIndex] = true;
  Serial.println("on");
}

void BLDC9::writeBLDC(int addr, data_bldc data)
{
  Wire.beginTransmission(0x50);
  Wire.write((int)(addr >> 8));
  Wire.write((int)(addr & 0xFF));
  Wire.write(data.onOff);
  Wire.write(data.direction);
  Wire.write(data.speed);
  Wire.endTransmission();
  delay(5);
}

BLDC9::data_bldc BLDC9::readBLDC(int addr)
{
  data_bldc data;
  Wire.beginTransmission(0x50);
  Wire.write((int)(addr >> 8));
  Wire.write((int)(addr & 0xFF));
  Wire.endTransmission();
  Wire.requestFrom(0x50, 4);
  if (Wire.available())
  {
    data.onOff = Wire.read();
    data.direction = Wire.read();
    data.speed = Wire.read();
  }

  return data;
}

int BLDC9::getStateDirection(int state, int bldcIndex)
{
  stateDirection[bldcIndex] = state;
  Serial.println(stateDirection[bldcIndex]);
  return stateDirection[bldcIndex];
}

int BLDC9::setStateDirection(int bldcIndex)
{
  return stateDirection[bldcIndex];
}