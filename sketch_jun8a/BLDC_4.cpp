#include "BLDC_4.h"
#include "ADDR.h"
#include <lvgl.h>
#include "ui.h"
#include "BLDC9.h"

BLDC9 myBLDC4;

const int bldcIndex4 = 3;

void ui_event_SliderSpeed4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    int16_t slider_value = lv_slider_get_value(target);

    if(event_code == LV_EVENT_VALUE_CHANGED) {
        slider[bldcIndex4] = slider_value;
        _ui_slider_set_text_value(ui_LabelSpeed4, target, "", "");
    }
}
void ui_event_Switch7(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    stateDirection[bldcIndex4] = 0;

    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) {
    // stateDirection = true;
        myBLDC4.getStateDirection(1, bldcIndex4);
        Serial.println("1");
    } else {
        // stateDirection = false;
        myBLDC4.getStateDirection(0, bldcIndex4);
        Serial.println("0");
    }
}
void ui_event_Switch8(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) { 
      myBLDC4.setOn(bldc4, bldcIndex4);
      lv_label_set_text(ui_LebelState4, "ON");

    } else {
      myBLDC4.setOff(bldc4, bldcIndex4);
      lv_label_set_text(ui_LebelState4, "OFF");
    }
}

void ui_event_Button17(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox3, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        BLDC9::data_bldc dataBLDC4 = myBLDC4.getData(speed[bldcIndex4], toggleOnOff[bldcIndex4], stateDirection[bldcIndex4]);
        myBLDC4.writeBLDC(ADDR_BLDC_4, dataBLDC4);
        myBLDC4.setSpeed(bldc4, slider[bldcIndex4], bldcIndex4);
        Serial.println("save");
    }
}
void ui_event_Button18(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox3, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        myBLDC4.setSpeed(bldc4, slider[bldcIndex4], bldcIndex4);
        Serial.println("no save");
    }
}