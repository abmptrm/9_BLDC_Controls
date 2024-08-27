#ifndef _BMP_H_
#define _BMP_H_

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_BMP280.h>

class BMP {
    private:

    public:
        void init(uint8_t addr);
        int write_press(uint8_t addr);
        int read_press(uint8_t addr, int val_press);
};

#endif
