// #ifndef _BLDC9_H_
// #define _BLDC9_H_

// #include <Arduino.h>
// #include <ESP32Servo.h>



// class BLDC9{
// private:
//     Servo bldc[8];

//     // access all files in cpp file
//     bool toggleOnOff = false;
//     int speed = 0; 
//     int stateDirection = 0;
//     int slider = 0;  
    
// public:

//     struct BLDCData {
//         int speed;
//         bool onOff; 
//         int direction;
//     };
    
//     void begin();
//     void setSpeed(Servo &BLDC, int slider);
//     void setOff(Servo &BLDC);
//     void setOn(Servo &BLDC);
//     void writeBLDC(unsigned int addr, BLDCData data);
//     BLDCData getData(int speed, int onOff, int direction);
//     BLDCData readBLDC(unsigned int addr);
//     int getStateDirection(int state);
//     int setStateDirection();
// };

// extern Servo bldc[8];



// #endif