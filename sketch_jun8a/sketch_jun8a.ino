#include <TFT_eSPI.h>
#include <EEPROM.h>

#include <lvgl.h>
#include "ui.h"

#include <Wire.h>
#include <BMP180.h>

#define EEPROM_SIZE 512

#define BLDC_1 0
#define BLDC_2 1
#define BLDC_3 2
#define BLDC_4 3
#define BLDC_5 4
#define BLDC_6 5
#define BLDC_7 6
#define BLDC_8 7
#define BLDC_9 8

uint16_t calData[5] = { 353, 3568, 269, 3491, 7};
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;

int state;
int readData;
// const char* value = "OFF";

lv_obj_t * ui_Label12;
lv_obj_t * ui_Label19;

lv_obj_t * ui_Label47;

/*
BMP180(resolution)

resolution:
BMP180_ULTRALOWPOWER - pressure oversampled 1 time  & power consumption 3μA
BMP180_STANDARD      - pressure oversampled 2 times & power consumption 5μA
BMP180_HIGHRES       - pressure oversampled 4 times & power consumption 7μA
BMP180_ULTRAHIGHRES  - pressure oversampled 8 times & power consumption 12μA, library default
*/

BMP180 myBMP(BMP180_ULTRAHIGHRES);

TFT_eSPI lcd = TFT_eSPI(); /* TFT entity */

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[ screenWidth * screenHeight / 13 ];


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

void setup()
{
  Serial.begin( 115200 ); /*serial init */

  EEPROM.begin(EEPROM_SIZE);
  
  //LCD init
  lcd.begin();          
  lcd.setRotation(1); 
  // lcd.fillScreen(TFT_BLACK);
  lcd.setTouch(calData);
  delay(100);
  //background light pin
  // pinMode(led, OUTPUT);
  // digitalWrite(27, HIGH);



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

  // lcd.fillScreen(TFT_BLACK);

  //lv_demo_widgets();    // LVGL demo
  ui_init();

  // while (myBMP.begin() != true)
  // {
  //   Serial.println(F("Bosch BMP180/BMP085 is not connected or fail to read calibration coefficients"));
  //   delay(5000);
  // }
  
  // Serial.println(F("Bosch BMP180/BMP085 sensor is OK")); //(F()) saves string to flash & keeps dynamic memory free

  

  Serial.println( "Setup done" );
}

// SCREEN BLDC 1 ======================================================================

void ui_event_Checkbox2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        if(lv_obj_has_state(target, LV_STATE_CHECKED)) {
            state = 1;
        } else {
            state = 0;
        }

        // Write the state to EEPROM
        EEPROM.write(0, state);
        EEPROM.commit();

        // Read back the state from EEPROM
        
        readData = EEPROM.read(0);

        // Update the label based on the state
        if (readData == 1) {
            lv_label_set_text(ui_Label47, "ON");
        } else if (readData == 0) {
            lv_label_set_text(ui_Label47, "OFF");
        }

        // Debug output to Serial Monitor
        Serial.print("Value: ");
        Serial.println(readData);
    }
    
    
}



void loop()
{
  // lv_label_set_text(ui_Label12, myBMP.getTemperature());
  // lv_label_set_text(ui_Label19, myBMP.getPressure());
  lv_timer_handler();
  delay(5);
}
