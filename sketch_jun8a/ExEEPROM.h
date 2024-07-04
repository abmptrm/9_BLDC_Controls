#ifndef _ExEEPROM_H_
#define _ExEEPROM_H_

#include <Arduino.h>
#include <Wire.h>

class ExEEPROM {
  public:
    
    void init();
    int write(int addr, int val);
    int read(int addr);  
  private:
    
};
#endif // ExEEPROM_H