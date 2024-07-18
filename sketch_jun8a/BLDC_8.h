#ifndef _BLDC_8_H_
#define _BLDC_8_H_

#include <lvgl.h>
#include <ESP32Servo.h>
#include "BLDC9.h"
#include "ui.h"


// extern int pin[0];
extern Servo bldc8;

// extern int slider[8] = { 0 };
// extern int speed[8] = { 0 };
// extern bool toggleOnOff[8] = { false };
// extern int stateDirection[8] = { 0 };



#ifdef __cplusplus
extern "C" {
#endif


void ui_event_SliderSpeed8(lv_event_t * e);
void ui_event_Switch15(lv_event_t * e);
void ui_event_Switch16(lv_event_t * e);
void ui_event_Button25(lv_event_t * e);
void ui_event_Button26(lv_event_t * e);

#ifdef __cplusplus
} // extern "C"
#endif

#endif