#include <TFT_eSPI.h>
#include <lvgl.h>
#include "ui.h"
#include <Arduino.h>
#include <ESP32Servo.h>
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

// Servo bldc1, bldc2;
// int bldcPin1 = 4;
// int bldcPin2 = 2;

// #include <Adafruit_AHT10.h>


uint16_t calData[5] = { 353, 3568, 269, 3491, 7};
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;

/*
BMP180(resolution)

resolution:
BMP180_ULTRALOWPOWER - pressure oversampled 1 time  & power consumption 3μA
BMP180_STANDARD      - pressure oversampled 2 times & power consumption 5μA
BMP180_HIGHRES       - pressure oversampled 4 times & power consumption 7μA
BMP180_ULTRAHIGHRES  - pressure oversampled 8 times & power consumption 12μA, library default
*/


// lv_obj_t * ui_LabelPress;
// lv_obj_t * ui_LabelTemp;
// lv_obj_t * ui_ContainerMsgBox;

TFT_eSPI lcd = TFT_eSPI(); /* TFT entity */

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[ screenWidth * screenHeight / 13 ];



// void update_motor_speed(int slider_value){ 
//   int speed;
//   if (stateWise == 1) {
//     speed = map(slider_value, 0, 100, 97, 120);
//   } 

//   if (stateWise == 0) {
//     speed = map(slider_value, 0, 100, 90, 73);
//   }  
//   bldc1.write(speed);        
// }


// Screen bldc1
// void ui_event_SliderSpeed1(lv_event_t * e)
// {
//     lv_event_code_t event_code = lv_event_get_code(e);
//     lv_obj_t * target = lv_event_get_target(e);

//     int16_t slider_value = lv_slider_get_value(target);


//     if(event_code == LV_EVENT_VALUE_CHANGED) {
//         _ui_slider_set_text_value(ui_LabelSpeed1, target, "", "");
//         int state_speed = state;
//         update_motor_speed(slider_value);
//     }
// }

// void ui_event_CheckboxState10(lv_event_t * e)
// {
//     lv_event_code_t event_code = lv_event_get_code(e);
//     lv_obj_t * target = lv_event_get_target(e);

//     if(event_code == lv_obj_has_state(target, LV_STATE_CHECKED)) {
//       clockwise = 1;
//     }
//     if(event_code == !lv_obj_has_state(target, LV_STATE_CHECKED)) {
//       clockwise = 0;
//     }

//     Serial.print("clock: ");
//     Serial.println(clockwise);
//     stateWise = clockwise;
// }

// void ui_event_CheckboxState1(lv_event_t * e)
// {
//     lv_event_code_t event_code = lv_event_get_code(e);
//     lv_obj_t * target = lv_event_get_target(e);
//     if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED)) {
//         _ui_label_set_property(ui_LebelState1, _UI_LABEL_PROPERTY_TEXT, "ON");
//     }
//     if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED)) {
//         _ui_label_set_property(ui_LebelState1, _UI_LABEL_PROPERTY_TEXT, "OFF");
//     }
// }

// //screen bldc 2

// void ui_event_SliderSpeed2(lv_event_t * e)
// {
//     lv_event_code_t event_code = lv_event_get_code(e);
//     lv_obj_t * target = lv_event_get_target(e);

//     int16_t slider_value = lv_slider_get_value(target);
//     if(event_code == LV_EVENT_VALUE_CHANGED) {
//         _ui_slider_set_text_value(ui_LabelSpeed2, target, "", "");
//         int speed = map(slider_value, 0, 100, 97, 120);
//         // update_motor_speed(speed);
//         bldc2.write(speed); 
//     }
// }

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

  // ESP32PWM::allocateTimer(0);
	// ESP32PWM::allocateTimer(1);
	// ESP32PWM::allocateTimer(2);
	// ESP32PWM::allocateTimer(3);
  // bldc1.setPeriodHertz(50);// Standard 50hz servo
  // bldc2.setPeriodHertz(50);// Standard 50hz servo

  // bldc1.attach(bldcPin1, 1000, 2000);
  // bldc2.attach(bldcPin2, 1000, 2000);
  // ESC.attach(signalOut,minPWM,maxPWM);

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
