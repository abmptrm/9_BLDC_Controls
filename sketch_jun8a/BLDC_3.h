#ifndef _BLDC_3_H_
#define _BLDC_3_H_

#include <lvgl.h>
#include <ESP32Servo.h>
#include "BLDC9.h"
#include "ui.h"


// extern int pin[0];
extern Servo bldc3;

// extern int slider[8] = { 0 };
// extern int speed[8] = { 0 };
// extern bool toggleOnOff[8] = { false };
// extern int stateDirection[8] = { 0 };



#ifdef __cplusplus
extern "C" {
#endif


void ui_event_SliderSpeed2(lv_event_t * e);
void ui_event_Switch3(lv_event_t * e);
void ui_event_Switch4(lv_event_t * e);
void ui_event_Button11(lv_event_t * e);
void ui_event_Button12(lv_event_t * e);

#ifdef __cplusplus
} // extern "C"
#endif

#endif