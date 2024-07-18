#include "BLDC_6.h"
#include "ADDR.h"
#include <lvgl.h>
#include "ui.h"
#include "BLDC9.h"

BLDC9 myBLDC6;
const int bldcIndex6 = 5;

void ui_event_SliderSpeed6(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    int16_t slider_value = lv_slider_get_value(target);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        slider[bldcIndex6] = slider_value;
        _ui_slider_set_text_value(ui_LabelSpeed6, target, "", "");
    }
}
void ui_event_Switch11(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    stateDirection[bldcIndex6] = 1;

    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) {
    // stateDirection = true;
        myBLDC6.getStateDirection(1, bldcIndex6);
        Serial.println("1");
    } else {
        // stateDirection = false;
        myBLDC6.getStateDirection(0, bldcIndex6);
        Serial.println("0");
    }
}
void ui_event_Switch12(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
     if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) { 
      myBLDC6.setOn(bldc6, bldcIndex6);
      lv_label_set_text(ui_LebelState6, "ON");

    } else {
      myBLDC6.setOff(bldc6, bldcIndex6);
      lv_label_set_text(ui_LebelState6, "OFF");
    }
}

void ui_event_Button21(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox5, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        BLDC9::data_bldc dataBLDC6 = myBLDC6.getData(speed[bldcIndex6], toggleOnOff[bldcIndex6], stateDirection[bldcIndex6]);
        myBLDC6.writeBLDC(ADDR_BLDC_2, dataBLDC6);
        myBLDC6.setSpeed(bldc6, slider[bldcIndex6], bldcIndex6);
        Serial.println("save");
    }
}
void ui_event_Button22(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox5, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}