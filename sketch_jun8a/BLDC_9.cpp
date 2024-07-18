#include "BLDC9.h"
#include "BLDC_9.h"
#include <ESP32Servo.h>
#include "ADDR.h"
#include <lvgl.h>
#include "ui.h"

BLDC9 myBLDC9;

const int bldcIndex9 = 8;

void ui_event_SliderSpeed9(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    int16_t slider_value = lv_slider_get_value(target);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        slider[bldcIndex9] = slider_value;
        _ui_slider_set_text_value(ui_LabelSpeed9, target, "", "");
    }
}
void ui_event_Switch17(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    stateDirection[bldcIndex9] = 1;

    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) {
        // stateDirection = true;
        myBLDC9.getStateDirection(0, bldcIndex9);
        //  
        Serial.println("1");
    } else {
        myBLDC9.getStateDirection(1, bldcIndex9);
        // stateDirection[bldcIndex7] = 0;
        // stateDirection = false;
        Serial.println("0");
    }
}
void ui_event_Switch18(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) { 
      myBLDC9.setOn(bldc9, bldcIndex9);
      lv_label_set_text(ui_LebelState9, "ON");
    } else {
      myBLDC9.setOff(bldc9, bldcIndex9);
      lv_label_set_text(ui_LebelState9, "OFF");
    }
}

void ui_event_Button27(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox8, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        BLDC9::data_bldc dataBLDC9 = myBLDC9.getData(speed[bldcIndex9], toggleOnOff[bldcIndex9], stateDirection[bldcIndex9]);
        myBLDC9.writeBLDC(ADDR_BLDC_9, dataBLDC9);
        myBLDC9.setSpeed(bldc9, slider[bldcIndex9], bldcIndex9);
        Serial.println("save");
    }
}
void ui_event_Button28(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox8, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        myBLDC9.setSpeed(bldc9, slider[bldcIndex9], bldcIndex9);
        Serial.println("no save");
    }
}