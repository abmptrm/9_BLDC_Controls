#ifndef _ENCODER_H
#define _ENCODER_H

#include <string.h>
#include <Arduino.h>

class Encoder {
    private:

    public: 

    void begin(int a, int b);
    int rpm();
    int read_rpm(int val);

};

#endif