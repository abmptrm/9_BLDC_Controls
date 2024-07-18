#ifndef _BLDC_7_H_
#define _BLDC_7_H_

#include <lvgl.h>
#include <ESP32Servo.h>
#include "BLDC9.h"
#include "ui.h"


// extern int pin[0];
extern Servo bldc7;

// extern int slider[8] = { 0 };
// extern int speed[8] = { 0 };
// extern bool toggleOnOff[8] = { false };
// extern int stateDirection[8] = { 0 };



#ifdef __cplusplus
extern "C" {
#endif


void ui_event_SliderSpeed7(lv_event_t * e);
void ui_event_Switch13(lv_event_t * e);
void ui_event_Switch14(lv_event_t * e);
void ui_event_Button23(lv_event_t * e);
void ui_event_Button24(lv_event_t * e);

#ifdef __cplusplus
} // extern "C"
#endif

#endif