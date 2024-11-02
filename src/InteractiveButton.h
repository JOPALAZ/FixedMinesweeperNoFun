#pragma once
#include "DrawableObject.h"
#include "SceneHandler.h"

class InteractiveButton : public baseInteractiveDrawableObject {
public:
    InteractiveButton(const std::string& textString, const std::string& signal,
                      SceneHandler* handler, double pivotX, double pivotY,
                      double spaceAllocationX, double spaceAllocationY,
                      sf::RenderWindow* window);

    void draw() override;
    void resize() override;

    int processMouse() override;
    void processInput() override;

private:
    std::string textString;
    std::string signal;
    SceneHandler* handler = nullptr;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape rectangle;

    double usefulSpaceX = 0.0;
    double usefulSpaceY = 0.0;
    const double padding = 0.05;
};
