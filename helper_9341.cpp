#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>
#include "Banggood9341_Hack.h"
#include "helper_9341.h"

#define XM A2
#define XP 6
#define YM 7
#define YP A1
#define MINPRESSURE 10
#define MAXPRESSURE 1000
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

bool helper_9341::s_started = false;
TouchScreen helper_9341::s_ts(XP, YP, XM, YM, 300);
Adafruit_TFTLCD helper_9341::s_tft(LCD_CS, LCD_RS, LCD_WR, LCD_RD, LCD_RESET);
TSPoint helper_9341::s_point;
extern void drawGUI();
extern void drawSS();

bool helper_9341::draw(const bool& force) {
  static bool sReDraw = true;
  static unsigned long sTime = 0;
  static unsigned long sLastDraw = 0;

  if (force) {
    sTime = millis();
    if (sReDraw) {
      drawGUI();
      sReDraw = false;
      return true;
    }
    return false;
  }
  if ((millis() - sTime) < 60000) {
    return false;
  }
  sReDraw = true;
  if ((millis() - sLastDraw) < 500) {
    return false;
  }
  drawSS();
  sLastDraw = millis();
  return false;
}

void helper_9341::fix() {
  int16_t tempX = helper_9341::s_point.x;

  helper_9341::s_point.x = 1023 - helper_9341::s_point.y;
  helper_9341::s_point.y = 1023 - tempX;
  helper_9341::s_point.x = map(helper_9341::s_point.x, TS_MINX, TS_MAXX, helper_9341::s_tft.width(), 0);
  helper_9341::s_point.y = map(helper_9341::s_point.y, TS_MINY, TS_MAXY, helper_9341::s_tft.height(), 0);
}

bool helper_9341::setup() {
  unsigned int id = 0;

  helper_9341::s_tft.reset();
  delay(500);
  id = helper_9341::s_tft.readID();
  if (id != 0x9341) {
    return false;
  }
  helper_9341::s_tft.begin(id);
  Lcd_Init();
  helper_9341::draw();
  return (helper_9341::s_started = true);
}

bool helper_9341::loop() {
  if (!helper_9341::s_started) {
    return false;
  }
  helper_9341::draw(false);
  helper_9341::s_point = helper_9341::s_ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if ((helper_9341::s_point.z < MINPRESSURE) || (helper_9341::s_point.z > MAXPRESSURE)) {
    return false;
  }
  if (helper_9341::draw()) {
    return false;
  }
  helper_9341::fix();
  return true;
}
