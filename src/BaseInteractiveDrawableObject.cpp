#include "DrawableObject.h"

bool baseInteractiveDrawableObject::mouseInBounds() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

    double left = pivotX * window->getSize().x;
    double top = pivotY * window->getSize().y;
    double width = spaceAllocationX * window->getSize().x;
    double height = spaceAllocationY * window->getSize().y;

    sf::FloatRect bounds(static_cast<float>(left), static_cast<float>(top),
                         static_cast<float>(width), static_cast<float>(height));

    return bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}
