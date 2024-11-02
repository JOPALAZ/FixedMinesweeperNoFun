#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class baseDrawableObject {
public:
    virtual void draw() = 0;
    virtual void resize() = 0;

    virtual void setPivotX(double val) { pivotX = val; }
    virtual void setPivotY(double val) { pivotY = val; }
    virtual void setAllocationX(double val) { spaceAllocationX = val; }
    virtual void setAllocationY(double val) { spaceAllocationY = val; }

protected:
    double pivotX = 0.0;
    double pivotY = 0.0;
    double spaceAllocationX = 1.0;
    double spaceAllocationY = 1.0;
};

class baseInteractiveDrawableObject : public baseDrawableObject {
public:
    virtual int processMouse() = 0;
    virtual void processInput() = 0;

    void setWindow(sf::RenderWindow* win) { window = win; }
    bool mouseInBounds();
    bool takesInput(){return this->takesInput_;}

protected:
    bool takesInput_ =  true;
    sf::RenderWindow* window = nullptr;
};

