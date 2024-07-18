#ifndef BLDC9_H
#define BLDC9_H

#include <Arduino.h>
#include <ESP32Servo.h>


extern bool toggleOnOff[8];
extern int speed[8];
extern int stateDirection[8];
extern int slider[8];

class BLDC9 {
private:

    
public:
    struct data_bldc {
      int speed;
      bool onOff; 
      int direction;
    };

    

    void begin(Servo &BLDC, int pin);
    void setSpeed(Servo &BLDC, int slider, int index);
    void setOff(Servo &BLDC, int index);
    void setOn(Servo &BLDC, int index);
    void writeBLDC(int addr, data_bldc data);
    data_bldc getData(int speed, int onOff, int direction);
    data_bldc readBLDC(int addr);
    int getStateDirection(int state, int index);
    int setStateDirection(int index);
};





#endif