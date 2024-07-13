#include "AHT10.h"
#include <Adafruit_AHT10.h>
#include <Arduino.h>  
#include <lvgl.h>
#include "ui.h"

lv_obj_t *ui_LabelTemp;
Adafruit_AHT10 aht;
Adafruit_Sensor *aht_temp;


void AHT10::init(){
    Serial.begin(115200);
    if (!aht.begin()) {
        Serial.println("Failed to find AHT10 chip");
        return;
    }
    aht_temp = aht.getTemperatureSensor(); // Correctly initialize aht_temp
    aht_temp->printSensorDetails();
    Serial.println("AHT10 Found!");
    // delay(100);
}

int AHT10::read_temp(int val_temp){
    if (val_temp > 0) {
        char my_temp[20];
        sprintf(my_temp, "%d°C", val_temp);
        Serial.print("r Temperature: ");
        Serial.println(my_temp); 
        // _ui_label_set_property(ui_LabelTemp, _UI_LABEL_PROPERTY_TEXT, my_temp);
        lv_label_set_text(ui_LabelTemp, my_temp);
    }
    return val_temp;
}

int AHT10::write_temp(){
    sensors_event_t temp, humidity;
    aht.getEvent(&humidity, &temp);
    int cs_temp = (int)temp.temperature;

    // data.write(ADDR_TEMP, cs_temp);

    char my_temp[20];
    sprintf(my_temp, "%d°C", cs_temp);
    Serial.print("w Temperature :");
    Serial.println(my_temp);
    // _ui_label_set_property(ui_LabelTemp, _UI_LABEL_PROPERTY_TEXT, my_temp);

    lv_label_set_text(ui_LabelTemp, my_temp);

    if (ui_LabelTemp != NULL) { // Ensure ui_LabelTemp is initialized
        lv_label_set_text(ui_LabelTemp, my_temp);
    } else {
        Serial.println("ui_LabelTemp is not initialized!");
    }
    return cs_temp;
    
}