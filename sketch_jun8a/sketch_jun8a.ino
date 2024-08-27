#include <Wire.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ESP32Servo.h>

#include "ui.h"
#include "ADDR.h"
// #include "SETUP.h"
#include "AHT10.h"
#include "BLDC9.h"
#include "BMP.h"
#include "ExEEPROM.h"
#include "eFirebase.h"
#include "BLDC_Controls.h"
#include "Encoder.h"

#define WIFI_SSID "ARIOESP32"
#define WIFI_PASSWORD "abim0999"
#define API_KEY "AIzaSyDIpeX5USkFPMXBNby5uzAuheMdy1RetmI"
#define DATABASE_URL "https://bldcv2-default-rtdb.asia-southeast1.firebasedatabase.app/"
// #define USER_EMAIL "admin-bldc9@itera.ac.id" // admin user
// #define USER_PASS "admin-bldc9-22-07-24" // admin pass

ExEEPROM data;
BMP s_press1, s_press2;
AHT10 aht10;
Encoder enc;

eFirebase fb;

BLDC9 BLDC;

bool run = false;

Servo bldc1, bldc2, bldc3, bldc4, bldc5, bldc6, bldc7, bldc8, bldc9;

const int pin[] = {15, 2, 4, 16, 17, 5, 19, 18, 23, 37};

uint16_t calData[5] = {353, 3568, 269, 3491, 7};
static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;

// unsigned long previousMillis = 0;
// const long interval = 10;

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

void sendData()
{
  int getSpeed[] = {
    map(data.read(ADDR_SPEED_1), 7, 65, 0, 100),
    map(data.read(ADDR_SPEED_2), 7, 65, 0, 100),
    map(data.read(ADDR_SPEED_3), 7, 65, 0, 100),
    map(data.read(ADDR_SPEED_4), 7, 65, 0, 100),
    map(data.read(ADDR_SPEED_5), 7, 65, 0, 100),
    map(data.read(ADDR_SPEED_6), 7, 65, 0, 100),
    map(data.read(ADDR_SPEED_7), 7, 65, 0, 100),
    map(data.read(ADDR_SPEED_8), 7, 65, 0, 100),
    map(data.read(ADDR_SPEED_9), 7, 65, 0, 100),
  };

  int val_temp = aht10.write_temp();
  data.write(ADDR_TEMP, val_temp);

  // int val_press1 = 1;

  int val_press1 = s_press1.write_press(0x77);
  data.write(ADDR_PRESS_B, val_press1);

  int val_press2 = s_press2.write_press(0x76);
  data.write(ADDR_PRESS_A, val_press2);

  // int val_press2 = 1;

  int val_rpm = enc.rpm();
  data.write(ADDR_SPEED_FAN, val_rpm);

  fb.sendData(getSpeed[0], getSpeed[1], getSpeed[2], getSpeed[3], getSpeed[4], getSpeed[5], getSpeed[6], getSpeed[7], getSpeed[8], val_temp, val_press1, val_press2, val_rpm);
}

///////////////// SETUP FUNCTIONS //////////////////

void setup()
{
  Serial.begin(115200); /*serial init */
  
  Wire.begin();

  fb.begin(WIFI_SSID, WIFI_PASSWORD, API_KEY, DATABASE_URL);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  BLDC.begin(bldc1, pin[0]);
  BLDC.begin(bldc2, pin[1]);
  BLDC.begin(bldc3, pin[2]);
  BLDC.begin(bldc4, pin[3]);
  BLDC.begin(bldc5, pin[4]);
  BLDC.begin(bldc6, pin[5]);
  BLDC.begin(bldc7, pin[6]);
  BLDC.begin(bldc8, pin[7]);
  BLDC.begin(bldc9, pin[8]);

  // BLDC.setOff(bldc1, 0);
  data.init();
  // bmp180_b.init();
  // bmp280_a.init();

  s_press1.init(0x77);
  s_press2.init(0x76);

  aht10.init();
  enc.begin(35, 34);



  init_lcd();
  
  int read_temp = data.read(ADDR_TEMP);
  int read_press1 = data.read(ADDR_PRESS_B);
  int read_press2 = data.read(ADDR_PRESS_A);
  readSensor(read_temp, read_press1, read_press2);
}

////////////////////// LOOP FUNCTIONS //////////////////

void loop()
{
  lv_task_handler();
  // yield();

  int getSpeed[] = {
    data.read(ADDR_SPEED_1),
    data.read(ADDR_SPEED_2),
    data.read(ADDR_SPEED_3),
    data.read(ADDR_SPEED_4),
    data.read(ADDR_SPEED_5),
    data.read(ADDR_SPEED_6),
    data.read(ADDR_SPEED_7),
    data.read(ADDR_SPEED_8),
    data.read(ADDR_SPEED_9)
  };

  if(run == true)
  {
    bldc1.write(getSpeed[0]);
    bldc2.write(getSpeed[1]);
    bldc3.write(getSpeed[2]);
    bldc4.write(getSpeed[3]);
    bldc5.write(getSpeed[4]);
    bldc6.write(getSpeed[5]);
    bldc7.write(getSpeed[6]);
    bldc8.write(getSpeed[7]);
    bldc9.write(getSpeed[8]);
  }

  if(run == false) {
    bldc1.write(6);
    bldc2.write(6);
    bldc3.write(6);
    bldc4.write(6);
    bldc5.write(6);
    bldc6.write(6);
    bldc7.write(6);
    bldc8.write(6);
    bldc9.write(6);
    
  }
  
  // sendData();

  delay(5);
}

void ui_event_Button29(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    run = false;
  }
}
void ui_event_Button31(lv_event_t *e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  if (event_code == LV_EVENT_CLICKED)
  {
    run = true;
  }
}
void readSensor(int temp, int press1, int press2)
{
  aht10.read_temp(temp);
  s_press1.read_press(0x77, press1);
  s_press2.read_press(0x76, press2);
}