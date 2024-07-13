#include "XBMP10.h"
#include <Arduino.h>  
#include <BMP180.h>
#include <Wire.h>
#include <lvgl.h>
#include "ui.h"

lv_obj_t *ui_LabelPress;

BMP180 myBMP(BMP180_ULTRAHIGHRES);

void XBMP10::init(){
  Serial.begin(115200);
  while (!myBMP.begin()){
    Serial.println(F("Bosch BMP180/BMP085 is not connected or fail to read calibration coefficients"));
    return;
  }
  
  Serial.println(F("Bosch BMP180/BMP085 sensor is OK")); //(F()) saves string to flash & keeps dynamic memory free
}


int XBMP10::write_press(){
    int cs_press = (int)myBMP.getPressure();
    char my_press[20];
    sprintf(my_press, "%dPa", cs_press);
    Serial.print("w Pressure: ");
    Serial.println(my_press); 
    // _ui_label_set_property(ui_LabelPress, _UI_LABEL_PROPERTY_TEXT, my_press);
    lv_label_set_text(ui_LabelPress, my_press);
    return cs_press;

}

int XBMP10::read_press(int val_press){
    if (val_press > 0){
        char my_press[20];
        sprintf(my_press, "%dPa", val_press);
        Serial.print("r Pressure: ");
        Serial.println(my_press); 
        // _ui_label_set_property(ui_LabelPress, _UI_LABEL_PROPERTY_TEXT, my_press);
        lv_label_set_text(ui_LabelPress, my_press);
      
    }
    return val_press;
}
