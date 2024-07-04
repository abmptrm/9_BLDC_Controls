#include "BLDC9.h"
#include <ESP32Servo.h> 
#include <Arduino.h>

BLDC9::BLDC9(int pinbldc1, int pinbldc2) :  pinBLDC1(pinbldc1), pinBLDC2(pinbldc2) {}

void BLDC9::begin(){
    Serial.begin(115200);
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    BLDC_1.setPeriodHertz(50);
    BLDC_2.setPeriodHertz(50);
    BLDC_1.attach(pinBLDC1, 0, 1000, 2000);
    BLDC_2.attach(pinBLDC2, 0, 1000, 2000);
    return; 
}


void BLDC9::setSpeed(Servo &BLDC, int slider_value){
    int speed;
    if (stateWise == 1) {
        speed = map(slider_value, 0, 100, 97, 120);
    } 

    if (stateWise == 0) {
        speed = map(slider_value, 0, 100, 90, 73);
    }  
    BLDC.write(speed);
    getSlider(slider_value);
}

int BLDC9::getSpeed(int speed) {
    return speed;
}

void setToggle(Servo &BLDC, int speed){
    if (speed > 0){ 
        setSpeed(BLDC, 0);
    } else {
        int speed_b = getSpeed(speed);
        setSpeed(BLDC, speed_b);
    }
}