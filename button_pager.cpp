#include <Arduino.h>
#include "button.h"
#include "button_pager.h"

extern button_pager bp;
int button_pager::sPage = 0;

button_pager::button_pager(int x, int y, int width, int height, unsigned int color, int type): button(x, y, width, height, color, ' ') {
  switch (this->mType = type) {
    case PAGER_LESS:
      this->setChar('-');
      break;
    case PAGER_PAGE:
      this->setChar('1' + button_pager::sPage);
      break;
    case PAGER_MORE:
      this->setChar('+');
      break;
  }
}

int button_pager::getPage() {
  return button_pager::sPage;
}

void button_pager::updateDisplay() {
  if (button_pager::sPage < 0) {
    button_pager::sPage = 3;
  }
  if (button_pager::sPage > 3) {
    button_pager::sPage = 0;
  }
  bp.setChar('1' + button_pager::sPage);
  bp.draw();
}

void button_pager::fire() {
  switch (this->mType) {
    case PAGER_LESS:
      --button_pager::sPage;
      this->updateDisplay();
      break;
    case PAGER_MORE:
      ++button_pager::sPage;
      this->updateDisplay();
      break;
  }
}

void button_pager::parse(const String& buffer) {
  if (!buffer.startsWith("p:")) {
    return;
  }
  switch (buffer[2]) {
    case '-':
      --button_pager::sPage;
      break;
    case '+':
      ++button_pager::sPage;
      break;
    default:
      button_pager::sPage = buffer[2] - '1';
      break;
  }
  this->updateDisplay();
}
