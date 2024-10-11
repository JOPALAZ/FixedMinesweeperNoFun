#include"DrawableObject.h"
#include"constants.h"
#include "SceneHandler.h"
bool baseInteractiveDrawableObject::mouseInBounds() {
  sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
  if ((mousePos.x > pivotX * window->getSize().x &&
        mousePos.x < pivotX * window->getSize().x +
                        window->getSize().x * spaceAllocationX) &&
      (mousePos.y > pivotY * window->getSize().y &&
        mousePos.y < pivotY * window->getSize().y +
                        window->getSize().y * spaceAllocationY)) {
    return true;
  }
  return false;
}
horizontalDrawableSplitter::horizontalDrawableSplitter(double splitterFactor, baseDrawableObject *obj1,
                            baseDrawableObject *obj2, double spaceX,
                            double spaceY, double pivotX, double pivotY) {
  spaceAllocationX = spaceX;
  spaceAllocationY = spaceY;
  this->pivotX = pivotX;
  this->pivotY = pivotY;
  this->splitterFactor = splitterFactor;
  if (obj1) {
    this->obj1 = obj1;
    obj1->setAllocationX(spaceAllocationX);
    obj1->setAllocationY(spaceAllocationY * splitterFactor);
    obj1->setPivotX(pivotX);
    obj1->setPivotY(pivotY);
  }
  if (obj2) {
    this->obj2 = obj2;
    obj2->setAllocationX(spaceAllocationX);
    obj2->setAllocationY(spaceAllocationY * (1.0 - splitterFactor));
    obj2->setPivotX(pivotX);
    obj2->setPivotY(pivotY + spaceAllocationY * splitterFactor);
  }
}
void horizontalDrawableSplitter::addObj(baseDrawableObject *obj) {
  if (obj) {
    if (!obj1) {
      obj1 = obj;
      obj1->setAllocationX(spaceAllocationX);
      obj1->setAllocationY(spaceAllocationY * splitterFactor);
      obj1->setPivotX(pivotX);
      obj1->setPivotY(pivotY);

    } else if (!obj2) {
      obj2 = obj;
      obj2->setAllocationX(spaceAllocationX);
      obj2->setAllocationY(spaceAllocationY * (1.0 - splitterFactor));
      obj2->setPivotX(pivotX);
      obj2->setPivotY(pivotY + spaceAllocationY * splitterFactor);
    }
  }
}
void horizontalDrawableSplitter::draw() {
  if (obj1) {
    obj1->draw();
  }
  if (obj2) {
    obj2->draw();
  }
}
void horizontalDrawableSplitter::setPivotX(double val) {
  this->pivotX = val;
  if (obj1) {
    obj1->setPivotX(pivotX);
  }
  if (obj2) {
    obj2->setPivotX(pivotX);
  }
}
void horizontalDrawableSplitter::setPivotY(double val) {
  this->pivotY = val;
  if (obj1) {
    obj1->setPivotY(pivotY);
  }
  if (obj2) {
    obj2->setPivotY(pivotY + spaceAllocationY * splitterFactor);
  }
}
void horizontalDrawableSplitter::setAllocationX(double val) {
  spaceAllocationX = val;
  if (obj1) {
    obj1->setAllocationX(spaceAllocationX);
  }
  if (obj2) {
    obj2->setAllocationX(spaceAllocationX);
  }
}
void horizontalDrawableSplitter::setAllocationY(double val) {
  spaceAllocationY = val;
  if (obj1) {
    obj1->setAllocationY(spaceAllocationY * splitterFactor);
  }
  if (obj2) {
    obj2->setAllocationY(spaceAllocationY * (1.0 - splitterFactor));
  }
}

void horizontalDrawableSplitter::resize() {
  if (obj1) {
    obj1->resize();
  }
  if (obj2) {
    obj2->resize();
  }
}
horizontalDrawableSplitter::~horizontalDrawableSplitter()
{
  if (obj1) {
    delete obj1;
  }
  if (obj2) {
    delete obj2;
  }
}
verticalDrawableSplitter::verticalDrawableSplitter(double splitterFactor, baseDrawableObject *obj1,
                          baseDrawableObject *obj2, double spaceX,
                          double spaceY, double pivotX, double pivotY) {
  spaceAllocationX = spaceX;
  spaceAllocationY = spaceY;
  this->pivotX = pivotX;
  this->pivotY = pivotY;
  this->splitterFactor = splitterFactor;
  if (obj1) {
    this->obj1 = obj1;
    obj1->setAllocationX(spaceAllocationX * splitterFactor);
    obj1->setAllocationY(spaceAllocationY);
    obj1->setPivotX(pivotX);
    obj1->setPivotY(pivotY);
  }
  if (obj2) {
    this->obj2 = obj2;
    obj2->setAllocationX(spaceAllocationX * (1.0 - splitterFactor));
    obj2->setAllocationY(spaceAllocationY);
    obj2->setPivotX(pivotX + spaceAllocationX * splitterFactor);
    obj2->setPivotY(pivotY);
  }
}
void verticalDrawableSplitter::addObj(baseDrawableObject *obj) {
  if (obj) {
    if (!obj1) {
      obj1 = obj;
      obj1->setAllocationX(spaceAllocationX * splitterFactor);
      obj1->setAllocationY(spaceAllocationY);
      obj1->setPivotX(pivotX);
      obj1->setPivotY(pivotY);
    } else if (!obj2) {
      obj2 = obj;
      obj2->setAllocationX(spaceAllocationX * (1.0 - splitterFactor));
      obj2->setAllocationY(spaceAllocationY);
      obj2->setPivotX(pivotX + spaceAllocationX * splitterFactor);
      obj2->setPivotY(pivotY);
    }
  }
}
void verticalDrawableSplitter::draw() {
  if (obj1) {
    obj1->draw();
  }
  if (obj2) {
    obj2->draw();
  }
}
void verticalDrawableSplitter::setPivotX(double val) {
  this->pivotX = val;
  if (obj1) {
    obj1->setPivotX(pivotX);
  }
  if (obj2) {
    obj2->setPivotX(pivotX + spaceAllocationX * splitterFactor);
  }
}
void verticalDrawableSplitter::setPivotY(double val) {
  this->pivotY = val;
  if (obj1) {
    obj1->setPivotY(pivotY);
  }
  if (obj2) {
    obj2->setPivotY(pivotY);
  }
}
void verticalDrawableSplitter::setAllocationX(double val) {
  spaceAllocationX = val;
  if (obj1) {
    obj1->setAllocationX(spaceAllocationX * splitterFactor);
  }
  if (obj2) {
    obj2->setAllocationX(spaceAllocationX * (1.0 - splitterFactor));
  }
}
void verticalDrawableSplitter::setAllocationY(double val) {
  spaceAllocationY = val;
  if (obj1) {
    obj1->setAllocationY(spaceAllocationY);
  }
  if (obj2) {
    obj2->setAllocationY(spaceAllocationY);
  }
}

void verticalDrawableSplitter::resize() {
  if (obj1) {
    obj1->resize();
  }
  if (obj2) {
    obj2->resize();
  }
}
  verticalDrawableSplitter::~verticalDrawableSplitter() {
  if (obj1) {
    delete obj1;
  }
  if (obj2) {
    delete obj2;
  }
}
InteractiveButton::InteractiveButton(std::string textString, Signal signal, SceneHandler *handler,
                    double pivotX, double pivotY, double spaceAllocationX,
                    double spaceAllocationY, sf::RenderWindow *window) {
    this->textString = textString;
    this->signal = signal;
    this->handler = handler;
    this->spaceAllocationX = spaceAllocationX;
    this->spaceAllocationY = spaceAllocationY;
    this->pivotX = pivotX;
    this->pivotY = pivotY;
    this->window = window;
    if (!font.loadFromFile("font.ttf")) {
      throw std::runtime_error("Cannot load necessary game data.");
    }
    this->text.setFont(font);
    this->text.setString(textString);
    this->rectangle.setFillColor(sf::Color::White);
    this->text.setCharacterSize(200);
    this->text.setFillColor(sf::Color::Black);
  }
  void InteractiveButton::draw() {
    window->draw(rectangle);
    window->draw(text);
  }
  void InteractiveButton::resize() {
    double textScaleX;
    double textScaleY;
    sf::FloatRect textRect;
    usefulSpaceX = window->getSize().x *
                   (spaceAllocationX - spaceAllocationX * padding * 2.f);
    usefulSpaceY = window->getSize().y *
                   (spaceAllocationY - spaceAllocationY * padding * 2.f);
    rectangle.setSize({(float)usefulSpaceX, (float)usefulSpaceY});
    rectangle.setOrigin(usefulSpaceX / 2.0, usefulSpaceY / 2.0);
    textScaleX = (usefulSpaceX * (1.0 - spaceAllocationX * padding)) /
                 text.getLocalBounds().width;
    textScaleY = (usefulSpaceY * (1.0 - spaceAllocationY * padding)) /
                 text.getLocalBounds().height;
    text.setScale(std::min(textScaleX, textScaleY),
                  std::min(textScaleX, textScaleY));
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition((pivotX + spaceAllocationX / 2) * window->getSize().x,
                     (pivotY + spaceAllocationY / 2) * window->getSize().y);
    rectangle.setPosition(text.getPosition());
  }
  int InteractiveButton::processMouse(){
    handler->takeSignal(signal);
    return -1;
  }
  void InteractiveButton::processInput() {
    handler->takeSignal(signal);
  }
  InteractiveButton::~InteractiveButton() =
      default; // since we dont allocate anything during runtime inside class
               // the default destructor will do just fine.