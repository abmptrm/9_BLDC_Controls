#include "BLDC_1.h"
#include "ADDR.h"
#include <lvgl.h>
#include "ui.h"
#include "BLDC9.h"

BLDC9 myBLDC1;


void ui_event_SliderSpeed1(lv_event_t * e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t * target = lv_event_get_target(e);

  int16_t slider_value = lv_slider_get_value(target);

  if(event_code == LV_EVENT_VALUE_CHANGED) {
    slider = slider_value;
    _ui_slider_set_text_value(ui_LabelSpeed1, target, "", "");
    // setSpeed(bldc1, slider_value);
  }
}

void ui_event_Switch2(lv_event_t * e) // CW/CCW
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t * target = lv_event_get_target(e);

  if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) {
    // stateDirection = true;
    myBLDC1.getStateDirection(1);
    Serial.println("1");
  } else {
    // stateDirection = false;
    myBLDC1.getStateDirection(0);
    Serial.println("0");
  }

}

void ui_event_Switch1(lv_event_t * e) // ON/OFF
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) { 
      myBLDC1.setOn(bldc1);

    } else {
      myBLDC1.setOff(bldc1);
    }
}


void ui_event_Button14(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        BLDC9::data_bldc dataBLDC1 = myBLDC1.getData(speed, toggleOnOff, stateDirection);
        myBLDC1.writeBLDC(ADDR_BLDC_1, dataBLDC1);
        myBLDC1.setSpeed(bldc1, slider);
        Serial.println("save");
     
    }
}
void ui_event_Button15(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        myBLDC1.setSpeed(bldc1, slider);
        Serial.println("no save");
        
    }
}
