#include "VerticalDrawableSplitter.h"

verticalDrawableSplitter::verticalDrawableSplitter(
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

void verticalDrawableSplitter::addObj(baseDrawableObject* obj) {
    if (!obj) return;

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

void verticalDrawableSplitter::draw() {
    if (obj1) obj1->draw();
    if (obj2) obj2->draw();
}

void verticalDrawableSplitter::setPivotX(double val) {
    pivotX = val;
    if (obj1) obj1->setPivotX(pivotX);
    if (obj2) obj2->setPivotX(pivotX + spaceAllocationX * splitterFactor);
}

void verticalDrawableSplitter::setPivotY(double val) {
    pivotY = val;
    if (obj1) obj1->setPivotY(pivotY);
    if (obj2) obj2->setPivotY(pivotY);
}

void verticalDrawableSplitter::setAllocationX(double val) {
    spaceAllocationX = val;
    if (obj1) obj1->setAllocationX(spaceAllocationX * splitterFactor);
    if (obj2) obj2->setAllocationX(spaceAllocationX * (1.0 - splitterFactor));
}

void verticalDrawableSplitter::setAllocationY(double val) {
    spaceAllocationY = val;
    if (obj1) obj1->setAllocationY(spaceAllocationY);
    if (obj2) obj2->setAllocationY(spaceAllocationY);
}

void verticalDrawableSplitter::resize() {
    if (obj1) obj1->resize();
    if (obj2) obj2->resize();
}

verticalDrawableSplitter::~verticalDrawableSplitter() {
    delete obj1;
    delete obj2;
}
