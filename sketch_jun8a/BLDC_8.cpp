#include "BLDC9.h"
#include "BLDC_8.h"
#include <ESP32Servo.h>
#include "ADDR.h"
#include <lvgl.h>
#include "ui.h"

BLDC9 myBLDC8;

const int bldcIndex8 = 7;

void ui_event_SliderSpeed8(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    int16_t slider_value = lv_slider_get_value(target);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        slider[bldcIndex8] = slider_value;
        _ui_slider_set_text_value(ui_LabelSpeed8, target, "", "");
    }
}
void ui_event_Switch15(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    stateDirection[bldcIndex8] = 1;

    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) {
        // stateDirection = true;
        myBLDC8.getStateDirection(0, bldcIndex8);
        //  
        Serial.println("1");
    } else {
        myBLDC8.getStateDirection(1, bldcIndex8);
        // stateDirection[bldcIndex7] = 0;
        // stateDirection = false;
        Serial.println("0");
    }
}
void ui_event_Switch16(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) { 
      myBLDC8.setOn(bldc8, bldcIndex8);
      lv_label_set_text(ui_LebelState8, "ON");
    } else {
      myBLDC8.setOff(bldc8, bldcIndex8);
      lv_label_set_text(ui_LebelState8, "OFF");
    }
}

void ui_event_Button25(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox7, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        BLDC9::data_bldc dataBLDC8 = myBLDC8.getData(speed[bldcIndex8], toggleOnOff[bldcIndex8], stateDirection[bldcIndex8]);
        myBLDC8.writeBLDC(ADDR_BLDC_8, dataBLDC8);
        myBLDC8.setSpeed(bldc8, slider[bldcIndex8], bldcIndex8);
        Serial.println("save");
    
    }
}
void ui_event_Button26(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox7, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        myBLDC8.setSpeed(bldc8, slider[bldcIndex8], bldcIndex8);
        Serial.println("no save");
        
    }
}