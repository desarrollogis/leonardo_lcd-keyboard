#include <Keyboard.h>
#include "button.h"
#include "button_pager.h"
#include "button_launcher.h"

button_launcher::button_launcher(int x, int y, int width, int height, unsigned int color, char c): button(x, y, width, height, color, c) {
  this->mLaunch[0] = String("#") + c + ":default";
  this->mLaunch[1] = String("#") + c + ":default";
  this->mLaunch[2] = String("#") + c + ":default";
  this->mLaunch[3] = String("#") + c + ":default";
}

void button_launcher::init() {
  Keyboard.begin();
}

void button_launcher::fire() {
  Keyboard.print(this->mLaunch[button_pager::getPage()]);
}

void button_launcher::parse(const String& buffer) {
  if (buffer.startsWith(String(this->mC) + ":")) {
    this->mLaunch[button_pager::getPage()] = buffer.substring(2);
  }
}
