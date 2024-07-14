#include <Wire.h>
#include <lvgl.h>
#include <Arduino.h>
#include <ESP32Servo.h> 
#include "ui.h"
#include "BLDC9.h"

bool toggleOnOff = false;
int speed = 0; 
int stateDirection = 0;
int slider = 0;  

struct data_bldc {
    int speed;
    bool onOff; 
    int direction;
};

void BLDC9::begin(Servo &BLDC, int pin){
    Serial.begin( 115200 ); 

    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

    BLDC.setPeriodHertz(50);
    BLDC.attach(pin, 1000, 2000);
    
    return;    
}

BLDC9::data_bldc BLDC9::getData(int speed, int onOff, int direction){
  data_bldc bldctest = {speed, onOff, direction};
  return bldctest;
}

void getSliderValue(int n_slider){
  slider = n_slider;
}

void BLDC9::setSpeed(Servo &BLDC, int slider_value){
    stateDirection = setStateDirection();
    if (stateDirection == 0) {
        speed = map(slider_value, 0, 100, 93, 62);
    } 

    if (stateDirection == 1) {
        speed = map(slider_value, 0, 100, 95, 125);
    }  

    BLDC.write(speed);
}

void BLDC9::setOff(Servo &BLDC){
    stateDirection = setStateDirection();
    if (stateDirection == 0) {
        BLDC.write(93);
    } 

    if (stateDirection == 1) {
        BLDC.write(95);
    }  

    toggleOnOff = false;
    
    Serial.println("off");
}

void BLDC9::setOn(Servo &BLDC){
    BLDC.write(speed);
    
    toggleOnOff = true;
    Serial.println("on");
}

void BLDC9::writeBLDC(int addr, data_bldc data) {
  Wire.beginTransmission(0x50);
  Wire.write((int)(addr >> 8));  
  Wire.write((int)(addr & 0xFF));
  Wire.write(data.onOff);
  Wire.write(data.direction);      
  Wire.write(data.speed);
  Wire.endTransmission();
  delay(5);
}

BLDC9::data_bldc BLDC9::readBLDC(int addr) {
  data_bldc data;
  Wire.beginTransmission(0x50);
  Wire.write((int)(addr >> 8));  
  Wire.write((int)(addr & 0xFF)); 
  Wire.endTransmission();
  Wire.requestFrom(0x50, 4); 
  if (Wire.available()) {
    data.onOff = Wire.read(); 
    data.direction = Wire.read(); 
    data.speed = Wire.read(); 
  }

  return data;
}

int BLDC9::getStateDirection(int state) {
  stateDirection = state;
  return stateDirection;
}

int BLDC9::setStateDirection(){
  return stateDirection;
}