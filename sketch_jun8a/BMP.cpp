#include "BMP.h"
#include <Wire.h>
#include <lvgl.h>
#include "ui.h"

Adafruit_BMP085_Unified bmp180 = Adafruit_BMP085_Unified(10085);
Adafruit_BMP280 bmp280;

lv_obj_t *ui_LabelPress;
lv_obj_t *ui_LabelPress2;

void BMP::init(uint8_t addr) {
  Serial.begin(115200);
  Wire.begin();

  if (addr == 0x77) {
    if (!bmp180.begin()) {
      Serial.println("Could not find a valid BMP180 sensor, check wiring!");
      return;
    }
    Serial.println(F("Bosch BMP180 sensor is OK"));
  }

  if (addr == 0x76) {
    if (!bmp280.begin(0x76)) {
      Serial.println("Could not find a valid BMP280 sensor, check wiring!");
      return;
    }
    Serial.println(F("Bosch BMP280 sensor is OK"));
  }
}

int BMP::write_press(uint8_t addr) {
  if (addr == 0x77) { 
    sensors_event_t event;
    bmp180.getEvent(&event);
    if (event.pressure) {
      int cs_press = (int)event.pressure / 100;
      char my_press[20];
      sprintf(my_press, "%dhPa", cs_press);
      Serial.println(my_press);
      
      if (ui_LabelPress != nullptr) {
        _ui_label_set_property(ui_LabelPress, _UI_LABEL_PROPERTY_TEXT, my_press);
      } else {
        Serial.println("ui_LabelPress is null");
      }
      return cs_press;
    }
  }

  if (addr == 0x76) {
    int cs_press = (int)bmp280.readPressure() / 100;
    char my_press[20];
    sprintf(my_press, "%dhPa", cs_press);
    Serial.println(my_press);
    
    if (ui_LabelPress2 != nullptr) {
      _ui_label_set_property(ui_LabelPress2, _UI_LABEL_PROPERTY_TEXT, my_press);
    } else {
      Serial.println("ui_LabelPress2 is null");
    }
    return cs_press;
  }
  return 0;
}

int BMP::read_press(uint8_t addr, int val_press) {
  int div_press = val_press / 100;
  if (div_press > 0 || div_press == 255) {
    char my_press[20];
    sprintf(my_press, "%dhPa", div_press);
    Serial.print(F("r Pressure: "));
    Serial.println(my_press); 

    if (addr == 0x77 && ui_LabelPress != nullptr) {
      _ui_label_set_property(ui_LabelPress, _UI_LABEL_PROPERTY_TEXT, my_press);
    } else if (addr == 0x76 && ui_LabelPress2 != nullptr) {
      _ui_label_set_property(ui_LabelPress2, _UI_LABEL_PROPERTY_TEXT, my_press);
    } else {
      Serial.println("Label is null");
    }
    return div_press;
  }
  return 0;
}