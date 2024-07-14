#ifndef _BLDC9_H_
#define _BLDC9_H_

#include <Arduino.h>
#include <ESP32Servo.h>

class BLDC9 {
private:
    
public:
    struct data_bldc {
      int speed;
      bool onOff; 
      int direction;
    };

    void begin(Servo &BLDC, int pin);
    void setSpeed(Servo &BLDC, int slider);
    void setOff(Servo &BLDC);
    void setOn(Servo &BLDC);
    void writeBLDC(int addr, data_bldc data);
    data_bldc getData(int speed, int onOff, int direction);
    data_bldc readBLDC(int addr);
    int getStateDirection(int state);
    int setStateDirection();
};




#endif