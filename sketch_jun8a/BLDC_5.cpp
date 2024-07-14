#include "BLDC_5.h"
#include "ADDR.h"
#include <lvgl.h>
#include "ui.h"
#include "BLDC9.h"

BLDC9 myBLDC5;

void ui_event_SliderSpeed5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    int16_t slider_value = lv_slider_get_value(target);

    if(event_code == LV_EVENT_VALUE_CHANGED) {
        slider = slider_value;
        _ui_slider_set_text_value(ui_LabelSpeed5, target, "", "");
    }
}
void ui_event_Switch9(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) {
    // stateDirection = true;
        myBLDC5.getStateDirection(1);
        Serial.println("1");
    } else {
        // stateDirection = false;
        myBLDC5.getStateDirection(0);
        Serial.println("0");
    }
}
void ui_event_Switch10(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) { 
      myBLDC5.setOn(bldc5);
      lv_label_set_text(ui_LebelState4, "ON");

    } else {
      myBLDC5.setOff(bldc5);
      lv_label_set_text(ui_LebelState4, "OFF");
    }
}

void ui_event_Button19(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox3, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        BLDC9::data_bldc dataBLDC5 = myBLDC5.getData(speed, toggleOnOff, stateDirection);
        myBLDC5.writeBLDC(ADDR_BLDC_2, dataBLDC5);
        myBLDC5.setSpeed(bldc5, slider);
        Serial.println("save");
    }
}
void ui_event_Button20(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox3, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        myBLDC5.setSpeed(bldc5, slider);
        Serial.println("no save");
    }
}