#include "BLDC_3.h"
#include "ADDR.h"
#include <lvgl.h>
#include "ui.h"
#include "BLDC9.h"

BLDC9 myBLDC3;

void ui_event_SliderSpeed3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    int16_t slider_value = lv_slider_get_value(target);

    if(event_code == LV_EVENT_VALUE_CHANGED) {
        slider = slider_value;
        _ui_slider_set_text_value(ui_LabelSpeed3, target, "", "");
    }
}
void ui_event_Switch5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) {
    // stateDirection = true;
        myBLDC3.getStateDirection(1);
        Serial.println("1");
    } else {
        // stateDirection = false;
        myBLDC3.getStateDirection(0);
        Serial.println("0");
    }
}
void ui_event_Switch6(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) { 
      myBLDC3.setOn(bldc3);
      lv_label_set_text(ui_LebelState3, "ON");

    } else {
      myBLDC3.setOff(bldc3);
      lv_label_set_text(ui_LebelState3, "OFF");
    }
}

void ui_event_Button13(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        BLDC9::data_bldc dataBLDC3 = myBLDC3.getData(speed, toggleOnOff, stateDirection);
        myBLDC3.writeBLDC(ADDR_BLDC_2, dataBLDC3);
        myBLDC3.setSpeed(bldc3, slider);
        Serial.println("save");
    }
}
void ui_event_Button16(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        myBLDC3.setSpeed(bldc3, slider);
        Serial.println("no save");
    }
}