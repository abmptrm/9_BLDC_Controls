#ifndef _BLDC_6_H_
#define _BLDC_6_H_

#include <lvgl.h>
#include <ESP32Servo.h>
#include "BLDC9.h"
#include "ui.h"


// extern int pin[0];
extern Servo bldc6;



#ifdef __cplusplus
extern "C" {
#endif


void ui_event_SliderSpeed6(lv_event_t * e);
void ui_event_Switch11(lv_event_t * e);
void ui_event_Switch12(lv_event_t * e);
void ui_event_Button21(lv_event_t * e);
void ui_event_Button22(lv_event_t * e);

#ifdef __cplusplus
} // extern "C"
#endif

#endif