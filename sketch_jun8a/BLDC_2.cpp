#include "BLDC9.h" 
#include "BLDC_2.h"
#include <lvgl.h>
#include <ESP32Servo.h>
#include "ui.h"
#include "ADDR.h"

BLDC9 myBLDC2;
// myBLDC2.getStateDirection(0);
const int bldcIndex2 = 1;

// int slider[8] = { 0 };
// int speed[8] = { 0 };
// bool toggleOnOff[8] = { false };
// int stateDirection[8] = { 0 };


void ui_event_SliderSpeed2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    int16_t slider_value = lv_slider_get_value(target);

    if(event_code == LV_EVENT_VALUE_CHANGED) {
        slider[bldcIndex2] = slider_value;
        
        _ui_slider_set_text_value(ui_LabelSpeed2, target, "", "");
    }
}
void ui_event_Switch3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    stateDirection[bldcIndex2] = 1;
    
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) {
        myBLDC2.getStateDirection(0, bldcIndex2);
        
    // stateDirection = true; 
        Serial.println("1");
        
    } else {
        myBLDC2.getStateDirection(1, bldcIndex2);
        // stateDirection[bldcIndex2] = 0;
        Serial.println("0");
    }
}
void ui_event_Switch4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) { 
      myBLDC2.setOn(bldc2, bldcIndex2);
      
      lv_label_set_text(ui_LebelState2, "ON");

    } else {
      myBLDC2.setOff(bldc2, bldcIndex2);

      lv_label_set_text(ui_LebelState2, "OFF");
    }
}

void ui_event_Button11(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        BLDC9::data_bldc dataBLDC2 = myBLDC2.getData(speed[bldcIndex2], toggleOnOff[bldcIndex2], stateDirection[bldcIndex2]);
        myBLDC2.writeBLDC(ADDR_BLDC_2, dataBLDC2);
        myBLDC2.setSpeed(bldc2, slider[bldcIndex2], bldcIndex2);
        Serial.println("save");
    }
}

void ui_event_Button12(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        myBLDC2.setSpeed(bldc2, slider[bldcIndex2], bldcIndex2);
        Serial.println("no save");
    }
}