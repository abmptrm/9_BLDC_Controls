#include "BLDC_Controls.h"
#include "eFirebase.h"
#include "BLDC9.h"
#include "ADDR.h"
#include "ui.h"

eFirebase db;

const int bldcIndex[] = {1, 2, 3, 4, 5, 6, 7, 8};
ExEEPROM eeprom;
BLDC9 myBLDC1, myBLDC2, myBLDC3, myBLDC4, myBLDC5, myBLDC6, myBLDC7, myBLDC8, myBLDC9;

// BLDC 1

void ui_event_SliderSpeed1(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);

  int16_t slider_value = lv_slider_get_value(target);

  if (event_code == LV_EVENT_VALUE_CHANGED)
  {
    slider[bldcIndex[0]] = slider_value;
    Serial.println(slider[bldcIndex[0]]);
    _ui_slider_set_text_value(ui_LabelSpeed1, target, "", "");
    // setSpeed(bldc1, slider_value);
  }
}

void ui_event_Switch1(lv_event_t *e) // ON/OFF
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (lv_obj_has_state(e->target, LV_STATE_CHECKED))
  {
    myBLDC1.setOn(bldc1, bldcIndex[0]);
    lv_label_set_text(ui_LebelState1, "ON");
  }
  else
  {
    myBLDC1.setOff(bldc1, bldcIndex[0], ADDR_SPEED_1);
    
    lv_label_set_text(ui_LebelState1, "OFF");
  }
}

void ui_event_Button14(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e); 
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // BLDC9::BLDC_DATA dataBLDC1 = myBLDC1.getData(speed[bldcIndex[0]], toggleOnOff[bldcIndex[0]]);
    // myBLDC1.writeBLDC(ADDR_SPEED_1, dataBLDC1);
    myBLDC1.setSpeed(bldc1, slider[bldcIndex[0]], bldcIndex[0]);
    
    delay(100);
    
    eeprom.write(ADDR_SPEED_1, speed[bldcIndex[0]]);
    delay(1);
    eeprom.write(ADDR_ONOFF_1, toggleOnOff[bldcIndex[0]]);
    delay(1);

    // fb.sendRealtimeData("/BLDC:1/Speed", speed[bldcIndex[0]], "bldc");
    // delay(100);

    

    // delay(100);
    // if (toggleOnOff[bldcIndex[0]] == true){
    // }

    Serial.println(F("save"));
  }
}
void ui_event_Button15(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // myBLDC1.setSpeed(bldc1, slider[bldcIndex[0]], bldcIndex[0]);
    Serial.println(F("no save"));
  }
}

// BLDC 2

void ui_event_SliderSpeed2(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);

  int16_t slider_value = lv_slider_get_value(target);

  if (event_code == LV_EVENT_VALUE_CHANGED)
  {
    slider[bldcIndex[1]] = slider_value;

    _ui_slider_set_text_value(ui_LabelSpeed2, target, "", "");
  }
}

void ui_event_Switch4(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (lv_obj_has_state(e->target, LV_STATE_CHECKED))
  {
    myBLDC2.setOn(bldc2, bldcIndex[1]);

    lv_label_set_text(ui_LebelState2, "ON");
  }
  else
  {
    myBLDC2.setOff(bldc2, bldcIndex[1], ADDR_SPEED_2);

    lv_label_set_text(ui_LebelState2, "OFF");
  }
}

void ui_event_Button11(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // BLDC9::BLDC_DATA dataBLDC2 = myBLDC2.getData(speed[bldcIndex[1]], toggleOnOff[bldcIndex[1]]);
    myBLDC2.setSpeed(bldc2, slider[bldcIndex[1]], bldcIndex[1]);
    // myBLDC2.writeBLDC(ADDR_SPEED_2, dataBLDC2);
    delay(100);
    eeprom.write(ADDR_SPEED_2, speed[bldcIndex[1]]);
    eeprom.write(ADDR_ONOFF_2, toggleOnOff[bldcIndex[1]]);
    Serial.println(F("save"));
  }
}

void ui_event_Button12(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox1, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    Serial.println(F("no save"));
  }
}

// BLDC 3
void ui_event_SliderSpeed3(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);

  int16_t slider_value = lv_slider_get_value(target);

  if (event_code == LV_EVENT_VALUE_CHANGED)
  {
    slider[bldcIndex[2]] = slider_value;
    _ui_slider_set_text_value(ui_LabelSpeed3, target, "", "");
  }
}

void ui_event_Switch6(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (lv_obj_has_state(e->target, LV_STATE_CHECKED))
  {
    myBLDC3.setOn(bldc3, bldcIndex[2]);
    lv_label_set_text(ui_LebelState3, "ON");
  }
  else
  {
    myBLDC3.setOff(bldc3, bldcIndex[2], ADDR_SPEED_3);
    lv_label_set_text(ui_LebelState3, "OFF");
  }
}

void ui_event_Button13(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // BLDC9::BLDC_DATA dataBLDC3 = myBLDC3.getData(speed[bldcIndex[2]], toggleOnOff[bldcIndex[2]]);
    myBLDC3.setSpeed(bldc3, slider[bldcIndex[2]], bldcIndex[2]);
    delay(100);
    eeprom.write(ADDR_SPEED_3, speed[bldcIndex[2]]);
    eeprom.write(ADDR_ONOFF_3, toggleOnOff[bldcIndex[2]]);
    Serial.println(F("save"));
  }
}
void ui_event_Button16(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox2, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // myBLDC3.setSpeed(bldc3, slider[bldcIndex[2]], bldcIndex[2]);
    Serial.println(F("no save"));
  }
}

// BLDC 4
void ui_event_SliderSpeed4(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);

  int16_t slider_value = lv_slider_get_value(target);

  if (event_code == LV_EVENT_VALUE_CHANGED)
  {
    slider[bldcIndex[3]] = slider_value;
    _ui_slider_set_text_value(ui_LabelSpeed4, target, "", "");
  }
}

void ui_event_Switch8(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (lv_obj_has_state(e->target, LV_STATE_CHECKED))
  {
    myBLDC4.setOn(bldc4, bldcIndex[3]);
    lv_label_set_text(ui_LebelState4, "ON");
  }
  else
  {
    myBLDC4.setOff(bldc4, bldcIndex[3], ADDR_SPEED_4);
    lv_label_set_text(ui_LebelState4, "OFF");
  }
}

void ui_event_Button17(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox3, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // BLDC9::BLDC_DATA dataBLDC4 = myBLDC4.getData(speed[bldcIndex[3]], toggleOnOff[bldcIndex[3]]);
    myBLDC4.setSpeed(bldc4, slider[bldcIndex[3]], bldcIndex[3]);
    delay(100);
    eeprom.write(ADDR_SPEED_4, speed[bldcIndex[3]]);
    eeprom.write(ADDR_ONOFF_4, toggleOnOff[bldcIndex[3]]);
    

    Serial.println(F("save"));
  }
}
void ui_event_Button18(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox3, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // myBLDC4.setSpeed(bldc4, slider[bldcIndex[3]], bldcIndex[3]);
    Serial.println(F("no save"));
  }
}

// BLDC 5
void ui_event_SliderSpeed5(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);

  int16_t slider_value = lv_slider_get_value(target);

  if (event_code == LV_EVENT_VALUE_CHANGED)
  {
    slider[bldcIndex[4]] = slider_value;
    _ui_slider_set_text_value(ui_LabelSpeed5, target, "", "");
  }
}

void ui_event_Switch10(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (lv_obj_has_state(e->target, LV_STATE_CHECKED))
  {
    myBLDC5.setOn(bldc5, bldcIndex[4]);
    lv_label_set_text(ui_LebelState5, "ON");
  }
  else
  {
    myBLDC5.setOff(bldc5, bldcIndex[4], ADDR_SPEED_5);
    lv_label_set_text(ui_LebelState5, "OFF");
  }
}

void ui_event_Button19(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox4, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    BLDC9::BLDC_DATA dataBLDC5 = myBLDC5.getData(speed[bldcIndex[4]], toggleOnOff[bldcIndex[4]]);
    myBLDC5.setSpeed(bldc5, slider[bldcIndex[4]], bldcIndex[4]);
    delay(100);
    eeprom.write(ADDR_SPEED_5, speed[bldcIndex[4]]);
    eeprom.write(ADDR_ONOFF_5, toggleOnOff[bldcIndex[4]]);
    
    Serial.println(F("save"));
  }
}
void ui_event_Button20(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox4, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // myBLDC5.setSpeed(bldc5, slider[bldcIndex[4]], bldcIndex[4]);
    Serial.println(F("no save"));
  }
}

// BLDC 6
void ui_event_SliderSpeed6(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  int16_t slider_value = lv_slider_get_value(target);
  if (event_code == LV_EVENT_VALUE_CHANGED)
  {
    slider[bldcIndex[5]] = slider_value;
    _ui_slider_set_text_value(ui_LabelSpeed6, target, "", "");
  }
}

void ui_event_Switch12(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (lv_obj_has_state(e->target, LV_STATE_CHECKED))
  {
    myBLDC6.setOn(bldc6, bldcIndex[5]);
    lv_label_set_text(ui_LebelState6, "ON");
  }
  else
  {
    myBLDC6.setOff(bldc6, bldcIndex[5], ADDR_SPEED_6);
    lv_label_set_text(ui_LebelState6, "OFF");
  }
}

void ui_event_Button21(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox5, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    BLDC9::BLDC_DATA dataBLDC6 = myBLDC6.getData(speed[bldcIndex[5]], toggleOnOff[bldcIndex[5]]);
    myBLDC6.setSpeed(bldc6, slider[bldcIndex[5]], bldcIndex[5]);
    delay(100);
    eeprom.write(ADDR_SPEED_6, speed[bldcIndex[5]]);
    eeprom.write(ADDR_ONOFF_6, toggleOnOff[bldcIndex[5]]);
    Serial.println(F("save"));
  }
}
void ui_event_Button22(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox5, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // myBLDC6.setSpeed(bldc6, slider[bldcIndex[5]], bldcIndex[5]);
    Serial.println(F("no save"));
  }
}

// BLDC 7

void ui_event_SliderSpeed7(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  int16_t slider_value = lv_slider_get_value(target);
  if (event_code == LV_EVENT_VALUE_CHANGED)
  {
    slider[bldcIndex[6]] = slider_value;
    _ui_slider_set_text_value(ui_LabelSpeed7, target, "", "");
  }
}

void ui_event_Switch14(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (lv_obj_has_state(e->target, LV_STATE_CHECKED))
  {
    myBLDC7.setOn(bldc7, bldcIndex[6]);
    lv_label_set_text(ui_LebelState7, "ON");
  }
  else
  {
    myBLDC7.setOff(bldc7, bldcIndex[6], ADDR_SPEED_7);
    lv_label_set_text(ui_LebelState7, "OFF");
  }
}

void ui_event_Button23(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox6, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // BLDC9::BLDC_DATA dataBLDC7 = myBLDC7.getData(speed[bldcIndex[6]], toggleOnOff[bldcIndex[6]]);
    myBLDC7.setSpeed(bldc7, slider[bldcIndex[6]], bldcIndex[6]);
    delay(100);
    eeprom.write(ADDR_SPEED_7, speed[bldcIndex[6]]);
    eeprom.write(ADDR_ONOFF_7, toggleOnOff[bldcIndex[6]]);
    Serial.println(F("save"));
  }
}
void ui_event_Button24(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox6, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // myBLDC7.setSpeed(bldc7, slider[bldcIndex[6]], bldcIndex[6]);
    Serial.println(F("no save"));
  }
}

// BLDC 8
void ui_event_SliderSpeed8(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  int16_t slider_value = lv_slider_get_value(target);
  if (event_code == LV_EVENT_VALUE_CHANGED)
  {
    slider[bldcIndex[7]] = slider_value;
    _ui_slider_set_text_value(ui_LabelSpeed8, target, "", "");
  }
}
void ui_event_Switch16(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (lv_obj_has_state(e->target, LV_STATE_CHECKED))
  {
    myBLDC8.setOn(bldc8, bldcIndex[7]);
    lv_label_set_text(ui_LebelState8, "ON");
  }
  else
  {
    myBLDC8.setOff(bldc8, bldcIndex[7], ADDR_SPEED_8);
    lv_label_set_text(ui_LebelState8, "OFF");
  }
}

void ui_event_Button25(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox7, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // BLDC9::BLDC_DATA dataBLDC8 = myBLDC8.getData(speed[bldcIndex[7]], toggleOnOff[bldcIndex[7]]);
    myBLDC8.setSpeed(bldc8, slider[bldcIndex[7]], bldcIndex[7]);
    delay(100);
    eeprom.write(ADDR_SPEED_8, speed[bldcIndex[7]]);
    eeprom.write(ADDR_ONOFF_8, toggleOnOff[bldcIndex[7]]);
    Serial.println(F("save"));
  }
}
void ui_event_Button26(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox7, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // myBLDC8.setSpeed(bldc8, slider[bldcIndex[7]], bldcIndex[7]);
    Serial.println(F("no save"));
  }
}

// BLDC 9
void ui_event_SliderSpeed9(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  int16_t slider_value = lv_slider_get_value(target);
  if (event_code == LV_EVENT_VALUE_CHANGED)
  {
    slider[bldcIndex[8]] = slider_value;
    _ui_slider_set_text_value(ui_LabelSpeed9, target, "", "");
  }
}
void ui_event_Switch18(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (lv_obj_has_state(e->target, LV_STATE_CHECKED))
  {
    myBLDC9.setOn(bldc9, bldcIndex[8]);
    lv_label_set_text(ui_LebelState9, "ON");
  }
  else
  {
    myBLDC9.setOff(bldc9, bldcIndex[8], ADDR_SPEED_9);
    lv_label_set_text(ui_LebelState9, "OFF");
  }
}

void ui_event_Button27(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox8, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // BLDC9::BLDC_DATA dataBLDC9 = myBLDC9.getData(speed[bldcIndex[8]], toggleOnOff[bldcIndex[8]]);
    myBLDC9.setSpeed(bldc9, slider[bldcIndex[8]], bldcIndex[8]);
    delay(100);
    eeprom.write(ADDR_SPEED_9, speed[bldcIndex[8]]);
    eeprom.write(ADDR_ONOFF_9, toggleOnOff[bldcIndex[8]]);
    Serial.println(F("save"));
  }
}
void ui_event_Button28(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    _ui_flag_modify(ui_ContainerMsgBox8, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    // myBLDC9.setSpeed(bldc9, slider[bldcIndex[8]], bldcIndex[8]);
    Serial.println(F("no save"));
  }
}