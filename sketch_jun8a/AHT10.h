#ifndef _AHT10_H_
#define _AHT10_H_

#include <Arduino.h>
#include <Adafruit_AHT10.h>

class AHT10 {
    public:
        // Constructor
        void init();
        int read_temp(int val_temp);
        int write_temp();

    private:
    
        // Data members if needed
};
extern Adafruit_AHT10 aht;
extern Adafruit_Sensor *aht_temp;

#endif