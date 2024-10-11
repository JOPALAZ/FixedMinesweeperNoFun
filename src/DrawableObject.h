
#pragma once
#include "constants.h"
#include <SFML/Graphics.hpp>
class SceneHandler;

class baseDrawableObject {
protected:
  double spaceAllocationX;
  double spaceAllocationY;
  double pivotX;
  double pivotY;
  sf::RenderWindow *window;

public:
  virtual void draw() = 0;
  virtual void resize() = 0;
  virtual void setAllocationX(double val) { spaceAllocationX = val; }
  virtual void setAllocationY(double val) { spaceAllocationY = val; }
  virtual void setPivotX(double val) { pivotX = val; }
  virtual void setPivotY(double val) { pivotY = val; }
  virtual void setRenderer(sf::RenderWindow *renderer) { window = renderer; }
  virtual ~baseDrawableObject() {}
};
class baseInteractiveDrawableObject : public baseDrawableObject {
protected:
  bool ended = false;

public:
  virtual void processInput() = 0;
  virtual bool takesInput() { return !ended; }
  virtual bool mouseInBounds();
  virtual int processMouse() = 0;
};
class horizontalDrawableSplitter : public baseDrawableObject {
protected:
  baseDrawableObject *obj1 = nullptr;
  baseDrawableObject *obj2 = nullptr;
  double splitterFactor;

public:
  horizontalDrawableSplitter(double splitterFactor, baseDrawableObject *obj1,
                             baseDrawableObject *obj2, double spaceX,
                             double spaceY, double pivotX, double pivotY);
  virtual void addObj(baseDrawableObject *obj);
  virtual void draw();
  virtual void setPivotX(double val) override;
  virtual void setPivotY(double val) override;
  virtual void setAllocationX(double val) override;
  virtual void setAllocationY(double val) override;
  virtual void resize() override;
  virtual baseDrawableObject *getObj1() { return obj1; }
  virtual baseDrawableObject *getObj2() { return obj2; }
  ~horizontalDrawableSplitter();
};
class verticalDrawableSplitter : public baseDrawableObject {
protected:
  baseDrawableObject *obj1 = nullptr;
  baseDrawableObject *obj2 = nullptr;
  double splitterFactor;

public:
  verticalDrawableSplitter() = default;
  verticalDrawableSplitter(double splitterFactor, baseDrawableObject *obj1,
                           baseDrawableObject *obj2, double spaceX,
                           double spaceY, double pivotX, double pivotY);
  virtual void addObj(baseDrawableObject *obj);
  virtual void draw() override;
  virtual void setPivotX(double val) override;
  virtual void setPivotY(double val) override;
  virtual void setAllocationX(double val) override;
  virtual void setAllocationY(double val) override;

  virtual void resize() override;
  virtual baseDrawableObject *getObj1() { return obj1; }
  virtual baseDrawableObject *getObj2() { return obj2; }
  virtual ~verticalDrawableSplitter();
};
class InteractiveButton : public baseInteractiveDrawableObject {
  std::string textString;
  Signal signal;
  sf::Font font;
  sf::RectangleShape rectangle;
  sf::Text text;
  SceneHandler *handler;
  double usefulSpaceX = 1;
  double usefulSpaceY = 1;

public:
  InteractiveButton(std::string textString, Signal signal, SceneHandler *handler,
                    double pivotX, double pivotY, double spaceAllocationX,
                    double spaceAllocationY, sf::RenderWindow *window);
  virtual void draw() override;
  virtual void resize() override;
  virtual int processMouse() override;
  virtual void processInput() override;
  ~InteractiveButton() =
      default; // since we dont allocate anything during runtime inside class
               // the default destructor will do just fine.
};
class verticalDrawableSplitterWithConstantRatio
    : public verticalDrawableSplitter {
  double pivotYObj1;
  double pivotXObj1;
  double spaceAllocationXObj1;
  double spaceAllocationYObj1;
  double aspectRatio;

public:
  verticalDrawableSplitterWithConstantRatio(
      double aspectRatio, double splitterFactor, baseDrawableObject *obj1,
      baseDrawableObject *obj2, double spaceX, double spaceY, double pivotX,
      double pivotY, sf::RenderWindow *window) {
    double possibleSpaceX;
    double possibleSpaceY;
    double realAspectRatio;
    this->splitterFactor = splitterFactor;
    this->aspectRatio = aspectRatio;
    spaceAllocationX = spaceX;
    spaceAllocationY = spaceY;
    this->pivotX = pivotX;
    this->pivotY = pivotY;
    this->window = window;
    possibleSpaceX = spaceAllocationX * splitterFactor * window->getSize().x;
    possibleSpaceY = window->getSize().y;
    realAspectRatio = possibleSpaceX / possibleSpaceY;
    if (realAspectRatio >= aspectRatio) {
      this->spaceAllocationYObj1 = this->spaceAllocationY;
      this->spaceAllocationXObj1 =
          this->spaceAllocationX * (aspectRatio / realAspectRatio);
      this->pivotXObj1 =
          this->pivotX +
          (spaceAllocationX - spaceAllocationXObj1) * splitterFactor / 2;
      this->pivotYObj1 = this->pivotY;
    } else {
      this->spaceAllocationXObj1 = this->spaceAllocationX;
      this->spaceAllocationYObj1 =
          this->spaceAllocationY * (realAspectRatio / aspectRatio);
      this->pivotYObj1 =
          this->pivotY + (spaceAllocationY - spaceAllocationYObj1) / 2;
      this->pivotXObj1 = this->pivotX;
    }
    if (obj1) {
      this->obj1 = obj1;
      obj1->setAllocationX(spaceAllocationXObj1 * splitterFactor);
      obj1->setAllocationY(spaceAllocationYObj1);
      obj1->setPivotX(pivotXObj1);
      obj1->setPivotY(pivotYObj1);
    }
    if (obj2) {
      this->obj2 = obj2;
      obj2->setAllocationX(spaceAllocationX * (1.0 - splitterFactor));
      obj2->setAllocationY(spaceAllocationY);
      obj2->setPivotX(pivotX + spaceAllocationX * splitterFactor);
      obj2->setPivotY(pivotY);
    }
  }
  virtual void addObj(baseDrawableObject *obj) {
    if (obj) {
      if (!obj1) {
        obj1 = obj;
        obj1->setAllocationX(spaceAllocationXObj1 * splitterFactor);
        obj1->setAllocationY(spaceAllocationYObj1);
        obj1->setPivotX(pivotXObj1);
        obj1->setPivotY(pivotYObj1);
      } else if (!obj2) {
        obj2 = obj;
        obj2->setAllocationX(spaceAllocationX * (1.0 - splitterFactor));
        obj2->setAllocationY(spaceAllocationY);
        obj2->setPivotX(pivotX + spaceAllocationX * splitterFactor);
        obj2->setPivotY(pivotY);
      }
    }
  }
  virtual void draw() override {
    if (obj1) {
      obj1->draw();
    }
    if (obj2) {
      obj2->draw();
    }
  }
  virtual void setPivotX(double val) override {
    this->pivotX = val;
    double possibleSpaceX;
    double possibleSpaceY;
    double realAspectRatio;
    possibleSpaceX = spaceAllocationX * splitterFactor * window->getSize().x;
    possibleSpaceY = window->getSize().y;
    realAspectRatio = possibleSpaceX / possibleSpaceY;
    if (realAspectRatio >= aspectRatio) {
      this->spaceAllocationYObj1 = this->spaceAllocationY;
      this->spaceAllocationXObj1 =
          this->spaceAllocationX * (aspectRatio / realAspectRatio);
      this->pivotXObj1 =
          this->pivotX +
          (spaceAllocationX - spaceAllocationXObj1) * splitterFactor / 2;
      this->pivotYObj1 = this->pivotY;
    } else {
      this->spaceAllocationXObj1 = this->spaceAllocationX;
      this->spaceAllocationYObj1 =
          this->spaceAllocationY * (realAspectRatio / aspectRatio);
      this->pivotYObj1 =
          this->pivotY + (spaceAllocationY - spaceAllocationYObj1) / 2;
      this->pivotXObj1 = this->pivotX;
    }
    if (obj1) {
      obj1->setPivotX(pivotXObj1);
    }
    if (obj2) {
      obj2->setPivotX(pivotX + spaceAllocationX * splitterFactor);
    }
  }
  virtual void setPivotY(double val) override {
    this->pivotY = val;
    double possibleSpaceX;
    double possibleSpaceY;
    double realAspectRatio;
    possibleSpaceX = spaceAllocationX * splitterFactor * window->getSize().x;
    possibleSpaceY = window->getSize().y;
    realAspectRatio = possibleSpaceX / possibleSpaceY;
    if (realAspectRatio >= aspectRatio) {
      this->spaceAllocationYObj1 = this->spaceAllocationY;
      this->spaceAllocationXObj1 =
          this->spaceAllocationX * (aspectRatio / realAspectRatio);
      this->pivotXObj1 =
          this->pivotX +
          (spaceAllocationX - spaceAllocationXObj1) * splitterFactor / 2;
      this->pivotYObj1 = this->pivotY;
    } else {
      this->spaceAllocationXObj1 = this->spaceAllocationX;
      this->spaceAllocationYObj1 =
          this->spaceAllocationY * (realAspectRatio / aspectRatio);
      this->pivotYObj1 =
          this->pivotY + (spaceAllocationY - spaceAllocationYObj1) / 2;
      this->pivotXObj1 = this->pivotX;
    }
    if (obj1) {
      obj1->setPivotY(pivotYObj1);
    }
    if (obj2) {
      obj2->setPivotY(pivotY);
    }
  }
  virtual void setAllocationX(double val) override {
    spaceAllocationX = val;
    double possibleSpaceX;
    double possibleSpaceY;
    double realAspectRatio;
    possibleSpaceX = spaceAllocationX * splitterFactor * window->getSize().x;
    possibleSpaceY = window->getSize().y;
    realAspectRatio = possibleSpaceX / possibleSpaceY;
    if (realAspectRatio >= aspectRatio) {
      this->spaceAllocationYObj1 = this->spaceAllocationY;
      this->spaceAllocationXObj1 =
          this->spaceAllocationX * (aspectRatio / realAspectRatio);
      this->pivotXObj1 =
          this->pivotX +
          (spaceAllocationX - spaceAllocationXObj1) * splitterFactor / 2;
      this->pivotYObj1 = this->pivotY;
    } else {
      this->spaceAllocationXObj1 = this->spaceAllocationX;
      this->spaceAllocationYObj1 =
          this->spaceAllocationY * (realAspectRatio / aspectRatio);
      this->pivotYObj1 =
          this->pivotY + (spaceAllocationY - spaceAllocationYObj1) / 2;
      this->pivotXObj1 = this->pivotX;
    }
    if (obj1) {
      obj1->setAllocationX(spaceAllocationXObj1 * splitterFactor);
    }
    if (obj2) {
      obj2->setAllocationX(spaceAllocationX * (1.0 - splitterFactor));
    }
  }
  virtual void setAllocationY(double val) override {
    spaceAllocationY = val;
    double possibleSpaceX;
    double possibleSpaceY;
    double realAspectRatio;
    possibleSpaceX = spaceAllocationX * splitterFactor * window->getSize().x;
    possibleSpaceY = window->getSize().y;
    realAspectRatio = possibleSpaceX / possibleSpaceY;
    if (realAspectRatio >= aspectRatio) {
      this->spaceAllocationYObj1 = this->spaceAllocationY;
      this->spaceAllocationXObj1 =
          this->spaceAllocationX * (aspectRatio / realAspectRatio);
      this->pivotXObj1 =
          this->pivotX +
          (spaceAllocationX - spaceAllocationXObj1) * splitterFactor / 2;
      this->pivotYObj1 = this->pivotY;
    } else {
      this->spaceAllocationXObj1 = this->spaceAllocationX;
      this->spaceAllocationYObj1 =
          this->spaceAllocationY * (realAspectRatio / aspectRatio);
      this->pivotYObj1 =
          this->pivotY + (spaceAllocationY - spaceAllocationYObj1) / 2;
      this->pivotXObj1 = this->pivotX;
    }
    if (obj1) {
      obj1->setAllocationY(spaceAllocationYObj1);
    }
    if (obj2) {
      obj2->setAllocationY(spaceAllocationY);
    }
  }

  virtual void resize() override {
    double possibleSpaceX;
    double possibleSpaceY;
    double realAspectRatio;
    possibleSpaceX = spaceAllocationX * splitterFactor * window->getSize().x;
    possibleSpaceY = window->getSize().y;
    realAspectRatio = possibleSpaceX / possibleSpaceY;
    if (realAspectRatio >= aspectRatio) {
      this->spaceAllocationYObj1 = this->spaceAllocationY;
      this->spaceAllocationXObj1 =
          this->spaceAllocationX * (aspectRatio / realAspectRatio);
      this->pivotXObj1 =
          this->pivotX +
          (spaceAllocationX - spaceAllocationXObj1) * splitterFactor / 2;
      this->pivotYObj1 = this->pivotY;
    } else {
      this->spaceAllocationXObj1 = this->spaceAllocationX;
      this->spaceAllocationYObj1 =
          this->spaceAllocationY * (realAspectRatio / aspectRatio);
      this->pivotYObj1 =
          this->pivotY + (spaceAllocationY - spaceAllocationYObj1) / 2;
      this->pivotXObj1 = this->pivotX;
    }
    if (obj1) {
      obj1->setAllocationX(spaceAllocationXObj1 * splitterFactor);
      obj1->setAllocationY(spaceAllocationYObj1);
      obj1->setPivotX(pivotXObj1);
      obj1->setPivotY(pivotYObj1);
      obj1->resize();
    }
    if (obj2) {
      obj2->setAllocationX(spaceAllocationX * (1.0 - splitterFactor));
      obj2->resize();
    }
  }
};