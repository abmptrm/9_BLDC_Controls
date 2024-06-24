#include <Wire.h>
// #define EEPROM_I2C_ADDRESS_0 0x50
// int EEPROM_I2C_ADDRESS = 0x50;

class EEPROM_AT24CXX {
  public:
    EEPROM_AT24CXX(); // Default Constructor
    void writeAT24(int addr, int val);
    int readAT24(int addr);
    void initEEPROM_AT24CXX();
  private:
    int EEPROM_I2C_ADDRESS = 0x50;
    //  readData = 0;

};

// CLASS

EEPROM_AT24CXX::EEPROM_AT24CXX(){}

void EEPROM_AT24CXX::initEEPROM_AT24CXX(){
  Wire.begin();
  delay(100);
  Serial.println("EEPROM_AT24CXX done.");
}

void EEPROM_AT24CXX::writeAT24(int addr, int val){
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(addr >> 8));   // MSB
  Wire.write((int)(addr & 0xFF)); // LSB
  Wire.write(val);
  Wire.endTransmission();
  delay(5);
}

int EEPROM_AT24CXX::readAT24(int addr){
  int readData = 0;
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(addr >> 8));   // MSB
  Wire.write((int)(addr & 0xFF)); // LSB
  Wire.endTransmission();

  delay(5);
  Wire.requestFrom(EEPROM_I2C_ADDRESS, 1);
  //delay(1);

  if(Wire.available())
  {
    readData =  Wire.read();
  }

  return readData;
}