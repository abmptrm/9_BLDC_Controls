#include <Wire.h>
#include <lvgl.h>
#include <BMP180.h>
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <ESP32Servo.h>
#include <Adafruit_AHT10.h>

#include "ui.h"
#include "ADDR.h"
#include "AHT10.h"
#include "BLDC9.h"
#include "XBMP10.h"
#include "ExEEPROM.h"

#include "BLDC_1.h"
#include "BLDC_2.h"
#include "BLDC_3.h"
#include "BLDC_4.h"
#include "BLDC_5.h"
#include "BLDC_6.h"
#include "BLDC_7.h"
#include "BLDC_8.h"
#include "BLDC_9.h"

ExEEPROM data;
XBMP10 bmp10;
AHT10 aht10;

BLDC9 myBLDC;

Servo bldc1, bldc2, bldc3, bldc4, bldc5, bldc6, bldc7, bldc8, bldc9;
int pin[] = {15, 2, 4, 16, 17, 5, 18, 19, 13};

uint16_t calData[5] = {353, 3568, 269, 3491, 7};
static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;

TFT_eSPI lcd = TFT_eSPI(); /* TFT entity */

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[screenWidth * screenHeight / 13];

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  lcd.startWrite();
  lcd.setAddrWindow(area->x1, area->y1, w, h);
  lcd.pushColors((uint16_t *)&color_p->full, w * h, true);
  lcd.endWrite();

  lv_disp_flush_ready(disp);
}

uint16_t touchX, touchY;

/*touch read*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{

  bool touched = lcd.getTouch(&touchX, &touchY, 600);
  if (!touched)
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

void init_lcd()
{
  // LCD init
  lcd.begin();
  lcd.setRotation(1);
  lcd.setTouch(calData);
  delay(100);

  // lvgl init
  lv_init();

  lv_disp_draw_buf_init(&draw_buf, buf1, NULL, screenWidth * screenHeight / 13);

  /* Initialize the display */
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /* Change the following line to your display resolution */
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /* Initialize the (dummy) input device driver */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  // lv_demo_widgets();    // LVGL demo
  ui_init();
}

///////////////// SETUP FUNCTIONS //////////////////

void setup()
{
  Serial.begin(115200); /*serial init */
  Wire.begin();
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);


  myBLDC.begin(bldc1, pin[0]);
  myBLDC.begin(bldc2, pin[1]);
  myBLDC.begin(bldc3, pin[2]);
  myBLDC.begin(bldc4, pin[3]);
  myBLDC.begin(bldc5, pin[4]);
  myBLDC.begin(bldc6, pin[5]);
  myBLDC.begin(bldc7, pin[6]);
  myBLDC.begin(bldc8, pin[7]);
  myBLDC.begin(bldc9, pin[8]);

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
