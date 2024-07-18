#include "BLDC9.h"
#include "BLDC_1.h"
#include <ESP32Servo.h>
#include "ADDR.h"
#include <lvgl.h>
#include "ui.h"

BLDC9 myBLDC1;

const int bldcIndex1 = 0;

// int slider[8] = { 0 };
// int speed[8] = { 0 };
// bool toggleOnOff[8] = { false };
// int stateDirection[8] = { 0 };

void ui_event_SliderSpeed1(lv_event_t * e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t * target = lv_event_get_target(e);

  int16_t slider_value = lv_slider_get_value(target);

  if(event_code == LV_EVENT_VALUE_CHANGED) {
    slider[bldcIndex1] = slider_value;
    _ui_slider_set_text_value(ui_LabelSpeed1, target, "", "");
    // setSpeed(bldc1, slider_value);
  }
}

void ui_event_Switch2(lv_event_t * e) // CW/CCW
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t * target = lv_event_get_target(e);

  stateDirection[bldcIndex1] = 1;

  if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) {
    // stateDirection = true;
    myBLDC1.getStateDirection(0, bldcIndex1);
    //  
    Serial.println("1");
  } else {
    myBLDC1.getStateDirection(1, bldcIndex1);
    // stateDirection[bldcIndex1] = 0;
    // stateDirection = false;
    Serial.println("0");
  }

}

void ui_event_Switch1(lv_event_t * e) // ON/OFF
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) { 
      myBLDC1.setOn(bldc1, bldcIndex1);
      lv_label_set_text(ui_LebelState1, "ON");
    } else {
      myBLDC1.setOff(bldc1, bldcIndex1);
      lv_label_set_text(ui_LebelState1, "OFF");
    }
}


void ui_event_Button14(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        BLDC9::data_bldc dataBLDC1 = myBLDC1.getData(speed[bldcIndex1], toggleOnOff[bldcIndex1], stateDirection[bldcIndex1]);
        myBLDC1.writeBLDC(ADDR_BLDC_1, dataBLDC1);
        myBLDC1.setSpeed(bldc1, slider[bldcIndex1], bldcIndex1);
        Serial.println("save");
     
    }
}
void ui_event_Button15(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        myBLDC1.setSpeed(bldc1, slider[bldcIndex1], bldcIndex1);
        Serial.println("no save");
        
    }
}
