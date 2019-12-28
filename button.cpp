#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>
#include "helper_9341.h"
#include "button.h"

#define DEBUG

extern Adafruit_TFTLCD tft;
uint8_t buf[8] = {0};
char button::sC = 0;
unsigned long button::sT = 0;

button::button(int x, int y, int width, int height, unsigned int color, char c) {
  this->mX = x;
  this->mY = y;
  this->mWidth = width;
  this->mHeight = height;
  this->mColor = color;
  this->mC = c;
}

void button::init() {
  Serial.begin(9600);
#if defined(__AVR_ATmega32U4__)
  delay(1000);
#endif
}

void button::draw() {
  helper_9341::s_tft.fillRect(this->mX + 2, this->mY + 2, this->mWidth - 4, this->mHeight - 4, this->mColor);
  helper_9341::s_tft.drawChar(this->mX + (this->mWidth / 2) - 12, this->mY + (this->mHeight / 2) - 24, this->mC, WHITE, this->mColor, 6);
}

void button::fire() {
#ifdef DEBUG
  Serial.println(this->mC);
#else
  buf[2] = this->mC - 'a' + 4;
  Serial.write(buf, 8);
  buf[2] = 0;
  Serial.write(buf, 8);
  buf[2] = 40;
  Serial.write(buf, 8);
  buf[2] = 0;
  Serial.write(buf, 8);
#endif
}

void button::erase() {
  helper_9341::s_tft.drawRect(this->mX, this->mY, this->mWidth, this->mHeight, BLACK);
  helper_9341::s_tft.drawRect(this->mX + 1, this->mY + 1, this->mWidth - 2, this->mHeight - 2, BLACK);
}

void button::stroke(int x, int y) {
  if (x < this->mX) {
    this->erase();
    return;
  }
  if (x >= (this->mX + this->mWidth)) {
    this->erase();
    return;
  }
  if (y < this->mY) {
    this->erase();
    return;
  }
  if (y >= (this->mY + this->mHeight)) {
    this->erase();
    return;
  }
  if (button::sC == this->mC) {
    if ((millis() - button::sT) <= 200) {
      return;
    }
  }
  button::sC = this->mC;
  button::sT = millis();
  helper_9341::s_tft.drawRect(this->mX, this->mY, this->mWidth, this->mHeight, WHITE);
  helper_9341::s_tft.drawRect(this->mX + 1, this->mY + 1, this->mWidth - 2, this->mHeight - 2, WHITE);
  this->fire();
}

void button::setChar(char c) {
  this->mC = c;
}
