#include "BLDC9.h"
#include "BLDC_7.h"
#include <ESP32Servo.h>
#include "ADDR.h"
#include <lvgl.h>
#include "ui.h"

BLDC9 myBLDC7;

const int bldcIndex7 = 6;

void ui_event_SliderSpeed7(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    int16_t slider_value = lv_slider_get_value(target);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        slider[bldcIndex7] = slider_value;
        _ui_slider_set_text_value(ui_LabelSpeed7, target, "", "");
    }
}
void ui_event_Switch13(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    stateDirection[bldcIndex7] = 1;

    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) {
        // stateDirection = true;
        myBLDC7.getStateDirection(0, bldcIndex7);
        //  
        Serial.println("1");
    } else {
        myBLDC7.getStateDirection(1, bldcIndex7);
        // stateDirection[bldcIndex7] = 0;
        // stateDirection = false;
        Serial.println("0");
    }
}
void ui_event_Switch14(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) { 
      myBLDC7.setOn(bldc7, bldcIndex7);
      lv_label_set_text(ui_LebelState7, "ON");
    } else {
      myBLDC7.setOff(bldc7, bldcIndex7);
      lv_label_set_text(ui_LebelState7, "OFF");
    }
}

void ui_event_Button23(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox6, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        BLDC9::data_bldc dataBLDC7 = myBLDC7.getData(speed[bldcIndex7], toggleOnOff[bldcIndex7], stateDirection[bldcIndex7]);
        myBLDC7.writeBLDC(ADDR_BLDC_7, dataBLDC7);
        myBLDC7.setSpeed(bldc7, slider[bldcIndex7], bldcIndex7);
        Serial.println("save");
    }
}
void ui_event_Button24(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox6, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        myBLDC7.setSpeed(bldc7, slider[bldcIndex7], bldcIndex7);
        Serial.println("no save");
        
    }
}