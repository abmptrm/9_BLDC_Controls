#ifndef _BLDC_1_H_
#define _BLDC_1_H_

#include <lvgl.h>
#include <ESP32Servo.h>
#include "BLDC9.h"
#include "ui.h"


// extern int pin[0];
extern Servo bldc3;
extern int slider;
extern int speed;
extern bool toggleOnOff;
extern int stateDirection;



#ifdef __cplusplus
extern "C" {
#endif


void ui_event_SliderSpeed3(lv_event_t * e);
void ui_event_Switch5(lv_event_t * e);
void ui_event_Switch6(lv_event_t * e);
void ui_event_Button13(lv_event_t * e);
void ui_event_Button16(lv_event_t * e);

#ifdef __cplusplus
} // extern "C"
#endif

#endif