#pragma once 
#include "DrawableObject.h"

class horizontalDrawableSplitter : public baseDrawableObject {
public:
    horizontalDrawableSplitter(double splitterFactor, baseDrawableObject* obj1 = nullptr,
                               baseDrawableObject* obj2 = nullptr, double spaceX = 1.0,
                               double spaceY = 1.0, double pivotX = 0.0, double pivotY = 0.0);

    void addObj(baseDrawableObject* obj);
    void draw() override;
    void resize() override;

    void setPivotX(double val) override;
    void setPivotY(double val) override;
    void setAllocationX(double val) override;
    void setAllocationY(double val) override;

    ~horizontalDrawableSplitter();

private:
    baseDrawableObject* obj1 = nullptr;
    baseDrawableObject* obj2 = nullptr;
    double splitterFactor = 0.5;
};