#ifndef _BLDC_4_H_
#define _BLDC_4_H_

#include <lvgl.h>
#include <ESP32Servo.h>
#include "BLDC9.h"
#include "ui.h"


// extern int pin[0];
extern Servo bldc4;



#ifdef __cplusplus
extern "C" {
#endif


void ui_event_SliderSpeed4(lv_event_t * e);
void ui_event_Switch7(lv_event_t * e);
void ui_event_Switch8(lv_event_t * e);
void ui_event_Button17(lv_event_t * e);
void ui_event_Button18(lv_event_t * e);

#ifdef __cplusplus
} // extern "C"
#endif

#endif