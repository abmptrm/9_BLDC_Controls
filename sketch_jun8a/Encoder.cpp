// #define ENCODER_A 21 // Pin for Encoder A
// #define ENCODER_B 22 // Pin for Encoder B
#include "Encoder.h"
// #include "ExEEPROM.h"
#include "ui.h"
#include "ADDR.h"
#include <lvgl.h>

// ExEEPROM save_rpm;

lv_obj_t * ui_LabelSpeed;

#define COUNTS_PER_REV 600

volatile int encoder_value = 0; 
unsigned long previousMillis = 0; 
const long interval = 1000; 
int val_rpm = 0;

int ENCODER_A;
int ENCODER_B;

void encoder_isr() {
  
  int A = digitalRead(ENCODER_A);
  int B = digitalRead(ENCODER_B);

  if ((A == HIGH) != (B == LOW)) {
    encoder_value--;
  } else {
    encoder_value++;
  }
}

void Encoder::begin(int a, int b){
    Serial.begin(115200);
    ENCODER_A = a;
    ENCODER_B = b;
    pinMode(ENCODER_A, INPUT);
    pinMode(ENCODER_B, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoder_isr, CHANGE);
}

int Encoder::rpm(){
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    char my_rpm[20];
    
    val_rpm = (int)(encoder_value * 60) / COUNTS_PER_REV;
    
    encoder_value = 0;
    
    sprintf(my_rpm, "%dRpm", val_rpm);
    lv_label_set_text(ui_LabelSpeed, my_rpm);
    // Serial.println("RPM: " + String(val_rpm));
    // save_rpm.write(ADDR_SPEED_FAN, rpm)
    return val_rpm;
  }
}

int Encoder::read_rpm(int val){
    char my_rpm[20];
    sprintf(my_rpm, "%dRpm", val);
    Serial.print(F("r rpm fan: "));
    Serial.println(my_rpm); 
    lv_label_set_text(ui_LabelSpeed, my_rpm);
    return val;
}