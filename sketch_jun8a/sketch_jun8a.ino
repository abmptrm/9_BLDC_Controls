#include <TFT_eSPI.h>

// #include <Wire.h>
// #define EEPROM_I2C_ADDRESS_0 0x50
// int EEPROM_I2C_ADDRESS = 0x50;
// int i=0;

#include "EEPROM_AT24CXX.h"
EEPROM_AT24CXX eeprom_data;



#include <lvgl.h>
#include "ui.h"

// #include <Wire.h>
#include <BMP180.h>

#include <Arduino.h>
#include <ESP32Servo.h>

Servo bldc1, bldc2;
int bldcPin1 = 4;
int bldcPin2 = 2;

#include <Adafruit_AHT10.h>

Adafruit_AHT10 aht;

Adafruit_Sensor *aht_humidity, *aht_temp;

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

// BMP180 myBMP(BMP180_ULTRAHIGHRES);

lv_obj_t * ui_LabelPress;
lv_obj_t * ui_LabelTemp;
lv_obj_t * ui_ContainerMsgBox;

TFT_eSPI lcd = TFT_eSPI(); /* TFT entity */

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[ screenWidth * screenHeight / 13 ];

int state;
int stateWise;
int clockwise = 1;

void update_motor_speed(int slider_value){ 
  int speed;
  if (stateWise == 1) {
    speed = map(slider_value, 0, 100, 97, 120);
  } 

  if (stateWise == 0) {
    speed = map(slider_value, 0, 100, 90, 73);
  }  
  bldc1.write(speed);        
}


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
  eeprom_data.initEEPROM_AT24CXX();

  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  bldc1.setPeriodHertz(50);// Standard 50hz servo
  bldc2.setPeriodHertz(50);// Standard 50hz servo

  bldc1.attach(bldcPin1, 1000, 2000);
  bldc2.attach(bldcPin2, 1000, 2000);

  // ESC.attach(signalOut,minPWM,maxPWM);

  init_lcd();

  // if (myBMP.begin() != true)
  // {
  //   Serial.println(F("Bosch BMP180/BMP085 is not connected or fail to read calibration coefficients"));
  //   delay(2000);
  // }

  // if (!aht.begin()) {
  //   Serial.println("Failed to find AHT10 chip");
  //   while (1) {
  //     delay(10);
  //   }
  // }

  // Serial.println("AHT10 Found!");
  // aht_temp = aht.getTemperatureSensor();
  // aht_temp->printSensorDetails();

  // EEPROM.begin(EEPROM_SIZE);
  // eeprom.begin();

  // Serial.println(F("Bosch BMP180/BMP085 sensor is OK")); //(F()) saves string to flash & keeps dynamic memory free

  // READ TEMPERATUR INTO EEPROM 
  // int val_temp = readAT24(0);

  // if (val_temp > 0){
  //   char my_temp[10];
  //   sprintf(my_temp, "%d", val_temp);
  //   _ui_label_set_property(ui_LabelTemp, _UI_LABEL_PROPERTY_TEXT, my_temp);
  // }

  // Serial.println( "Setup done" );

}

////////////////////// LOOP FUNCTIONS //////////////////

void loop()
{
  lv_task_handler();

  // WRITE TEMP INTO EEPROM
  // sensors_event_t temp, humidity;
  // aht.getEvent(&humidity, &temp);
  // Serial.print("Temperature ");
  // Serial.println(temp.temperature);
  // int cs_temp = (int)temp.temperature;

  // writeAT24(0, cs_temp);

  // char my_temp[10];
  // sprintf(my_temp, "%d", cs_temp);
  // _ui_label_set_property(ui_LabelTemp, _UI_LABEL_PROPERTY_TEXT, my_temp);

  /////////////////////////////////////

  // // Serial.print(F("Temperature.......: ")); Serial.print(myBMP.getTemperature(), 1); Serial.println(F(" +-1.0C"));
  // Serial.print(F("Pressure..........: ")); Serial.print(myBMP.getPressure());       Serial.println(F(" +-100Pa"));

  // int cs_press = (int)myBMP.getPressure();
  // char my_press[10];
  // sprintf(my_press, "%d", cs_press);
  // _ui_label_set_property(ui_LabelPress, _UI_LABEL_PROPERTY_TEXT, my_press);

  

  delay(2);
  
  
  
  // lv_label_set_text(ui_Label19, myBMP.getPressure());

  

  // lv_label_set_text(, );
}


// Function to write to EEPROOM
// void writeAT24(int dataAddress, int dataVal)
// {
//   Wire.beginTransmission(EEPROM_I2C_ADDRESS);

//   Wire.write((int)(dataAddress >> 8));   // MSB
//   Wire.write((int)(dataAddress & 0xFF)); // LSB
//   Wire.write(dataVal);
//   Wire.endTransmission();

//   delay(5);
// }

// // Function to read from EEPROM
// byte readAT24(int dataAddress)
// {
//   byte readData = 0;
//   Wire.beginTransmission(EEPROM_I2C_ADDRESS);
//   Wire.write((int)(dataAddress >> 8));   // MSB
//   Wire.write((int)(dataAddress & 0xFF)); // LSB
//   Wire.endTransmission();

//   delay(5);
//   Wire.requestFrom(EEPROM_I2C_ADDRESS, 1);
//   //delay(1);

//   if(Wire.available())
//   {
//     readData =  Wire.read();
//   }

//   return readData;
// }





