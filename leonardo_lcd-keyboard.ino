#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>
#include "helper_9341.h"
#include "button.h"
#include "button_launcher.h"
#include "button_pager.h"

button_launcher b1(0, 0, 120, 120, RED, '1');
button_launcher b2(120, 0, 120, 120, GREEN, '2');
button_launcher b3(0, 120, 120, 120, BLUE, '3');
button_launcher b4(120, 120, 120, 120, YELLOW, '4');
button_pager bl(0, 240, 80, 80, CYAN, PAGER_LESS);
button_pager bp(80, 240, 80, 80, MAGENTA, PAGER_PAGE);
button_pager bm(160, 240, 80, 80, CYAN, PAGER_MORE);
String sBuffer = "";

void drawGUI() {
  helper_9341::s_tft.fillScreen(BLACK);
  b1.draw();
  b2.draw();
  b3.draw();
  b4.draw();
  bl.draw();
  bp.draw();
  bm.draw();
}

void drawSS() {
  int x = random(240 - 20);
  int y = random(320 - 20);
  int color = random();

  helper_9341::s_tft.fillRect(x, y, 20, 20, color);
}

void setup() {
  button::init();
  button_launcher::init();
  if (!helper_9341::setup()) {
    return;
  }
}

void loop() {
  while (Serial.available()) {
    sBuffer = Serial.readStringUntil('\n');
    b1.parse(sBuffer);
    b2.parse(sBuffer);
    b3.parse(sBuffer);
    b4.parse(sBuffer);
    bp.parse(sBuffer);
  }
  if (!helper_9341::loop()) {
    return;
  }
  b1.stroke(helper_9341::s_point.x, helper_9341::s_point.y);
  b2.stroke(helper_9341::s_point.x, helper_9341::s_point.y);
  b3.stroke(helper_9341::s_point.x, helper_9341::s_point.y);
  b4.stroke(helper_9341::s_point.x, helper_9341::s_point.y);
  bl.stroke(helper_9341::s_point.x, helper_9341::s_point.y);
  bp.stroke(helper_9341::s_point.x, helper_9341::s_point.y);
  bm.stroke(helper_9341::s_point.x, helper_9341::s_point.y);
}
