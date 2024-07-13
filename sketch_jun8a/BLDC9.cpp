// #include "BLDC9.h"
// #include <ESP32Servo.h> 
// #include <Arduino.h>
// #include <Wire.h>
// #include <lvgl.h>
// #include "ui.h"

// bool toggleOnOff = false;
// int speed = 0; 
// int stateDirection = 0;
// int slider = 0;  

// Servo bldc[8];
// int pin[] = {15, 2, 4, 16, 17, 5, 18, 19, 13};

// void BLDC9::begin(){
//     Serial.begin( 115200 ); 

//     ESP32PWM::allocateTimer(0);
// 	ESP32PWM::allocateTimer(1);
// 	ESP32PWM::allocateTimer(2);
// 	ESP32PWM::allocateTimer(3);

//     for (int i = 0; i < 8; i++)
//     {   
//         bldc[i].setPeriodHertz(50);
//         bldc[i].attach(pin[i], 1000, 2000);
//     }
    
// }

// // BLDCData BLDC9::getData(int speed, int onOff, int direction){
// //   BLDCData bldctest = {speed, onOff, direction};
// //   return bldctest;
// // }

// void getSliderValue(int n_slider){
//   slider = n_slider;
// }

// void BLDC9::setSpeed(Servo &BLDC, int slider_value){
//     stateDirection = setStateDirection();
//     if (stateDirection == 0) {
//         speed = map(slider_value, 0, 100, 93, 62);
//     } 

//     if (stateDirection == 1) {
//         speed = map(slider_value, 0, 100, 95, 125);
//     }  

//     BLDC.write(speed);
// }

// void BLDC9::setOff(Servo &BLDC){
//     stateDirection = setStateDirection();
//     if (stateDirection == 0) {
//         BLDC.write(93);
//     } 

//     if (stateDirection == 1) {
//         BLDC.write(95);
//     }  

//     toggleOnOff = false;
//     lv_label_set_text(ui_LebelState1, "OFF");
//     Serial.println("off");
// }

// void BLDC9::setOn(Servo &BLDC){
//     BLDC.write(speed);
//     lv_label_set_text(ui_LebelState1, "ON");
//     toggleOnOff = true;
//     Serial.println("on");
// }

// void BLDC9::writeBLDC(unsigned int addr, BLDCData data) {
//   Wire.beginTransmission(0x50);
//   Wire.write((int)(addr >> 8));  
//   Wire.write((int)(addr & 0xFF));
//   Wire.write(data.onOff);
//   Wire.write(data.direction);      
//   Wire.write(data.speed);
//   Wire.endTransmission();
//   delay(5);
// }

// // BLDCData BLDC9::readBLDC(unsigned int addr) {
// //   BLDCData data;
// //   Wire.beginTransmission(0x50);
// //   Wire.write((int)(addr >> 8));  
// //   Wire.write((int)(addr & 0xFF)); 
// //   Wire.endTransmission();
// //   Wire.requestFrom(0x50, 4); 
// //   if (Wire.available()) {
// //     data.onOff = Wire.read(); 
// //     data.direction = Wire.read(); 
// //     data.speed = Wire.read(); 
// //   }

// //   return data;
// // }

// int BLDC9::getStateDirection(int state) {
//   stateDirection = state;
//   return stateDirection;
// }

// int BLDC9::setStateDirection(){
//   return stateDirection;
// }