#include "HorizontalDrawableSplitter.h"

horizontalDrawableSplitter::horizontalDrawableSplitter(
    double splitterFactor, baseDrawableObject* obj1, baseDrawableObject* obj2,
    double spaceX, double spaceY, double pivotX, double pivotY)
{
    this->splitterFactor = splitterFactor;
    spaceAllocationX = spaceX;
    spaceAllocationY = spaceY;
    this->pivotX = pivotX;
    this->pivotY = pivotY;

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

void horizontalDrawableSplitter::addObj(baseDrawableObject* obj) {
    if (!obj) return;

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

void horizontalDrawableSplitter::draw() {
    if (obj1) obj1->draw();
    if (obj2) obj2->draw();
}

void horizontalDrawableSplitter::setPivotX(double val) {
    pivotX = val;
    if (obj1) obj1->setPivotX(pivotX);
    if (obj2) obj2->setPivotX(pivotX);
}

void horizontalDrawableSplitter::setPivotY(double val) {
    pivotY = val;
    if (obj1) obj1->setPivotY(pivotY);
    if (obj2) obj2->setPivotY(pivotY + spaceAllocationY * splitterFactor);
}

void horizontalDrawableSplitter::setAllocationX(double val) {
    spaceAllocationX = val;
    if (obj1) obj1->setAllocationX(spaceAllocationX);
    if (obj2) obj2->setAllocationX(spaceAllocationX);
}

void horizontalDrawableSplitter::setAllocationY(double val) {
    spaceAllocationY = val;
    if (obj1) obj1->setAllocationY(spaceAllocationY * splitterFactor);
    if (obj2) obj2->setAllocationY(spaceAllocationY * (1.0 - splitterFactor));
}

void horizontalDrawableSplitter::resize() {
    if (obj1) obj1->resize();
    if (obj2) obj2->resize();
}

horizontalDrawableSplitter::~horizontalDrawableSplitter() {
    delete obj1;
    delete obj2;
}
