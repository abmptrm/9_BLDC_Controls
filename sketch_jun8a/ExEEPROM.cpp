#include "ExEEPROM.h"
#include <Arduino.h>  
#include <Wire.h>

#define EEPROM_ADDR 0x50

void ExEEPROM::init(){
    Serial.begin(115200);
  Wire.begin();
  Serial.println("EEPROM Is Ready!");
}

int ExEEPROM::write(int addr, int val){
    // Wire.begin();
    Wire.beginTransmission(EEPROM_ADDR);
    Wire.write((int)(addr >> 8));   // MSB
    Wire.write((int)(addr & 0xFF)); // LSB
    Wire.write(val);
    int result = Wire.endTransmission();
    delay(5); // Ensure EEPROM write cycle time
    return result; 
}

int ExEEPROM::read(int addr){
    int readData = 0;
    // Wire.begin();
    Wire.beginTransmission(EEPROM_ADDR);
    Wire.write((int)(addr >> 8));   // MSB
    Wire.write((int)(addr & 0xFF)); // LSB
    Wire.endTransmission();
    delay(5);
    Wire.requestFrom(EEPROM_ADDR, 1);
    if (Wire.available()) {
        readData =  Wire.read();
    } else {
        Serial.println("Error: No data available from EEPROM");
    }

    return readData;
}