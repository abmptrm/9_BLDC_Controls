#include <TFT_eSPI.h>
#include <lvgl.h>
#include "ui.h"
#include <Arduino.h>
#include <ESP32Servo.h>
#include "BLDC9.h"
#include "ExEEPROM.h"
#include <Adafruit_AHT10.h>
#include <BMP180.h>
#include "XBMP10.h"
#include "AHT10.h"
#include "ADDR.h"
#include <Wire.h>

ExEEPROM data;
XBMP10 bmp10;
AHT10 aht10;
// Adafruit_AHT10 aht;
// Adafruit_Sensor *aht_humidity, *aht_temp;
// BMP180 myBMP(BMP180_ULTRAHIGHRES);

Servo bldc1, bldc2;
int bldc_pin[] = {15, 2, 4, 16, 17, 5, 18, 19, 13}; // to 9 pin bldc
// BLDC9 myBLDC;

uint16_t calData[5] = { 353, 3568, 269, 3491, 7};
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;

TFT_eSPI lcd = TFT_eSPI(); /* TFT entity */

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[ screenWidth * screenHeight / 13 ];

struct BLDCData {
    int speed;
    bool onOff; 
    int direction;
};

// FUNCTION BLDC
bool toggleOnOff = false;
int speed = 0; 
int stateDirection = 0;
int slider = 0;

                                                                                                                 
// Fungsi untuk menulis struktur data ke EEPROM
void writeBLDCDataToEEPROM(unsigned int address, BLDCData data) {
  Wire.beginTransmission(0x50);
  Wire.write((int)(address >> 8));  // Kirim byte alamat tinggi
  Wire.write((int)(address & 0xFF)); // Kirim byte alamat rendah
  Wire.write(data.onOff);            // Kirim status on/off
  Wire.write(data.direction);        // Kirim arah rotasi
  Wire.write(data.speed); // Kirim kecepatan
  Wire.endTransmission();
  delay(5); // Beri waktu EEPROM untuk menyelesaikan operasi tulis
}

BLDCData readBLDCDataFromEEPROM(unsigned int address) {
  BLDCData data;
  Wire.beginTransmission(0x50);
  Wire.write((int)(address >> 8));  // Kirim byte alamat tinggi
  Wire.write((int)(address & 0xFF)); // Kirim byte alamat rendah
  Wire.endTransmission();
  Wire.requestFrom(0x50, 4); // Meminta 4 byte data
  if (Wire.available()) {
    data.onOff = Wire.read(); // Baca status on/off
    data.direction = Wire.read(); // Baca arah rotasi
    data.speed = Wire.read(); // Baca kecepatan
  }
  return data;
}


BLDCData getData(int speed, int onOff, int direction){
  BLDCData bldctest = {speed, onOff, direction};
  return bldctest;
}

void setSpeed(Servo &BLDC, int slider_value){ 
  // int speed;
  // speed = map(slider_value, 0, 100, 100, 120);
  stateDirection = setStateDirection();
  if (stateDirection == 0) {
    speed = map(slider_value, 0, 100, 93, 62);
  } 

  if (stateDirection == 1) {
    speed = map(slider_value, 0, 100, 95, 125);
  }  

  // return speed;
  // getSpeed(speed);
  BLDC.write(speed);
  // return slider_value;     
  
}

void setOff(Servo &BLDC){
  // const int off = 0;
  // speed = map(100, 0, 100, 94, 93);
  // BLDC.write(94);
  stateDirection = setStateDirection();
  if (stateDirection == 0) {
    // speed = map(slider_value, 0, 100, 93, 62);
    BLDC.write(93);
  } 

  if (stateDirection == 1) {
    // speed = map(slider_value, 0, 100, 95, 125);
    BLDC.write(95);
  }  
  
  // speed = 0;
  // _ui_slider_set_text_value(ui_LabelSpeed1, 0, "", "");
  toggleOnOff = false;
  lv_label_set_text(ui_LebelState1, "OFF");
  Serial.println("off");
  // lv_obj_add_state(ui_SliderSpeed1, LV_STATE_DISABLED);
  

}

void setOn(Servo &BLDC){
  BLDC.write(speed);
  
  lv_label_set_text(ui_LebelState1, "ON");
  toggleOnOff = true;
  Serial.println("on");
  // lv_obj_clear_state(ui_SliderSpeed1, LV_STATE_DISABLED);
  
}
   

// Screen BLDC 1
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

void ui_event_Switch1(lv_event_t * e) // ON/OFF
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) { 
      setOn(bldc1);

    } else {
      setOff(bldc1);
    }
}

int getStateDirection(int state) {
  stateDirection = state;
  return stateDirection;
}

int setStateDirection(){
  return stateDirection;
}

void ui_event_Switch2(lv_event_t * e) // CW/CCW
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t * target = lv_event_get_target(e);

  if(lv_obj_has_state(e->target, LV_STATE_CHECKED)) {
    // stateDirection = true;
    getStateDirection(1);
    Serial.println("1");
  } else {
    // stateDirection = false;
    getStateDirection(0);
    Serial.println("0");
  }

}

void BLDCEEPROM (){}
void ui_event_Button14(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        BLDCData dataBLDC1 = getData(speed, toggleOnOff, stateDirection);
        writeBLDCDataToEEPROM(ADDR_BLDC_1, dataBLDC1);
        setSpeed(bldc1, slider);
        Serial.println("save");
     
    }
}
void ui_event_Button15(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_ContainerMsgBox, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        setSpeed(bldc1, slider);
        Serial.println("no save");
        
    }
}
  


void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
  uint32_t w = ( area->x2 - area->x1 + 1 );
  uint32_t h = ( area->y2 - area->y1 + 1 );

  lcd.startWrite();
  lcd.setAddrWindow( area->x1, area->y1, w, h );
  lcd.pushColors( ( uint16_t * )&color_p->full, w * h, true );
  lcd.endWrite();

  lv_disp_flush_ready( disp );
}

uint16_t touchX, touchY;

/*touch read*/
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{

  bool touched = lcd.getTouch( &touchX, &touchY, 600);
  if ( !touched )
  {
    data->state = LV_INDEV_STATE_REL;
  }
  else
  {
    data->state = LV_INDEV_STATE_PR;

    /*set location*/
    data->point.x = touchX;
    data->point.y = touchY;

    // Serial.print( "Data x " );
    // Serial.println( touchX );

    // Serial.print( "Data y " );
    // Serial.println( touchY );
  }
}

void init_lcd(){
  //LCD init
  lcd.begin();          
  lcd.setRotation(1); 
  lcd.setTouch(calData);
  delay(100);

  //lvgl init
  lv_init();
  
  lv_disp_draw_buf_init( &draw_buf, buf1, NULL, screenWidth * screenHeight / 13 );

  /* Initialize the display */
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  /* Change the following line to your display resolution */
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );

  /* Initialize the (dummy) input device driver */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register( &indev_drv );

  //lv_demo_widgets();    // LVGL demo
  ui_init();
}


///////////////// SETUP FUNCTIONS //////////////////

void setup()
{
  Serial.begin( 115200 ); /*serial init */
  Wire.begin();

  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  bldc1.setPeriodHertz(50);// Standard 50hz servo
  bldc2.setPeriodHertz(50);// Standard 50hz servo

  bldc1.attach(bldc_pin[0], 1000, 2000);
  bldc2.attach(bldc_pin[1], 1000, 2000);

  // myBLDC.begin();

  // setOff(bldc1);

  data.init();
  bmp10.init();
  aht10.init();
  

  init_lcd();

  int read_temp = data.read(ADDR_TEMP);
  aht10.read_temp(read_temp);
  int read_press = data.read(ADDR_PRESS);
  bmp10.read_press(read_press);
  
  
  // Serial.println( "Setup done" );

}

////////////////////// LOOP FUNCTIONS //////////////////

void loop()
{
  lv_task_handler();
  int val_temp = aht10.write_temp();
  data.write(ADDR_TEMP, val_temp);
  int val_press = bmp10.write_press();
  data.write(ADDR_PRESS, val_press);
  delay(2);
  // delay(5);
}
