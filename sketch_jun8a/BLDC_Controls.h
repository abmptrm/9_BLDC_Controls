#ifndef BLDC_Controls_H
#define BLDC_Controls_H

#include <lvgl.h>
#include <ESP32Servo.h>
// #include "BLDC9.h"
#include "ui.h"

extern Servo bldc1, bldc2, bldc3, bldc4, bldc5, bldc6, bldc7, bldc8, bldc9;

// extern int slider[8] = { 0 };
// extern int speed[8] = { 0 };
// extern bool toggleOnOff[8] = { false };
// extern int stateDirection[8] = { 0 };

#ifdef __cplusplus
extern "C" {
#endif

// BLDC 1
void ui_event_SliderSpeed1(lv_event_t * e);
void ui_event_Switch1(lv_event_t * e);
void ui_event_Button14(lv_event_t * e);
void ui_event_Button15(lv_event_t * e);

// BLDC 2
void ui_event_SliderSpeed2(lv_event_t * e);
void ui_event_Switch4(lv_event_t * e);
void ui_event_Button11(lv_event_t * e);
void ui_event_Button12(lv_event_t * e);

// BLDC 3
void ui_event_SliderSpeed3(lv_event_t * e);
void ui_event_Switch6(lv_event_t * e);
void ui_event_Button13(lv_event_t * e);
void ui_event_Button16(lv_event_t * e);

// BLDC 4
void ui_event_SliderSpeed4(lv_event_t * e);
void ui_event_Switch8(lv_event_t * e);
void ui_event_Button17(lv_event_t * e);
void ui_event_Button18(lv_event_t * e);

// BLDC 5 
void ui_event_SliderSpeed5(lv_event_t * e);
void ui_event_Switch10(lv_event_t * e);
void ui_event_Button19(lv_event_t * e);
void ui_event_Button20(lv_event_t * e);

// BLDC 6
void ui_event_SliderSpeed6(lv_event_t * e);
void ui_event_Switch12(lv_event_t * e);
void ui_event_Button21(lv_event_t * e);
void ui_event_Button22(lv_event_t * e);

// BLDC 7
void ui_event_SliderSpeed7(lv_event_t * e);
void ui_event_Switch14(lv_event_t * e);
void ui_event_Button23(lv_event_t * e);
void ui_event_Button24(lv_event_t * e);

// BLDC 8
void ui_event_SliderSpeed8(lv_event_t * e);
void ui_event_Switch16(lv_event_t * e);
void ui_event_Button25(lv_event_t * e);
void ui_event_Button26(lv_event_t * e);

// BLDC 9
void ui_event_SliderSpeed9(lv_event_t * e);
void ui_event_Switch17(lv_event_t * e);
void ui_event_Switch18(lv_event_t * e);
void ui_event_Button27(lv_event_t * e);
void ui_event_Button28(lv_event_t * e);
#ifdef __cplusplus
} // extern "C"
#endif

#endif