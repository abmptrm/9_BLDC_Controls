#ifndef _XBMP10_H_
#define _XBMP10_H_

#include <Arduino.h>
#include <Wire.h>
#include <BMP180.h>

class XBMP10 {
    public:
        void init();
        int write_press();
        int read_press(int val_press);
};

// extern BMP180 myBMP(BMP180_ULTRAHIGHRES);

#endif
