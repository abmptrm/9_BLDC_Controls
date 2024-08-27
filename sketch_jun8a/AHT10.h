#ifndef _AHT10_H_
#define _AHT10_H_

#include <Arduino.h>
#include <Adafruit_AHT10.h>

class AHT10 {
    public:
        // Constructor
        void init();
        uint8_t read_temp(uint8_t val_temp);
        uint8_t write_temp();

    private:
    
        // Data members if needed
};
extern Adafruit_AHT10 aht;
extern Adafruit_Sensor *aht_temp;

#endif