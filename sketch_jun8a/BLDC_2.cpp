#include "BLDC_2.h"
#include "ADDR.h"
#include <lvgl.h>
#include "ui.h"
#include "BLDC9.h"

BLDC9 myBLDC2;

void ui_event_SliderSpeed2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    int16_t slider_value = lv_slider_get_value(target);

    if(event_code == LV_EVENT_VALUE_CHANGED) {
        slider = slider_value;
        
        _ui_slider_set_text_value(ui_LabelSpeed2, target, "", "");
    }
}
void ui_event_Switch3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) {
    // stateDirection = true;
    myBLDC2.getStateDirection(1);
    Serial.println("1");
    } else {
        // stateDirection = false;
        myBLDC2.getStateDirection(0);
        Serial.println("0");
    }
}
void ui_event_Switch4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) { 
      myBLDC2.setOn(bldc2);

    } else {
      myBLDC2.setOff(bldc2);
    }
}

void ui_event_Button11(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        BLDC9::data_bldc dataBLDC2 = myBLDC2.getData(speed, toggleOnOff, stateDirection);
        myBLDC2.writeBLDC(ADDR_BLDC_2, dataBLDC2);
        myBLDC2.setSpeed(bldc2, slider);
        Serial.println("save");
    }
}

void ui_event_Button12(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        myBLDC2.setSpeed(bldc2, slider);
        Serial.println("no save");
    }
}