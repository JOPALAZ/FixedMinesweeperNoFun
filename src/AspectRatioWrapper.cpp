#include "AspectRatioWrapper.h"

AspectRatioWrapper::AspectRatioWrapper(baseDrawableObject* object, double aspectRatio,
                                       double spaceX, double spaceY,
                                       double pivotX, double pivotY,
                                       sf::RenderWindow* window)
{
    this->object = object;
    this->aspectRatio = aspectRatio;
    this->spaceAllocationX = spaceX;
    this->spaceAllocationY = spaceY;
    this->pivotX = pivotX;
    this->pivotY = pivotY;
    this->window = window;

    recalculateDimensions();

    if (object) {
        object->setAllocationX(adjustedSpaceX);
        object->setAllocationY(adjustedSpaceY);
        object->setPivotX(adjustedPivotX);
        object->setPivotY(adjustedPivotY);
    }
}

AspectRatioWrapper::~AspectRatioWrapper() {
    delete object;
}

void AspectRatioWrapper::recalculateDimensions() {
    if (!window) return;

    double windowWidth = window->getSize().x;
    double windowHeight = window->getSize().y;

    double availableWidth = spaceAllocationX * windowWidth;
    double availableHeight = spaceAllocationY * windowHeight;

    double currentAspectRatio = availableWidth / availableHeight;

    if (currentAspectRatio > aspectRatio) {
        // Ширина слишком большая, уменьшаем ширину
        adjustedSpaceY = spaceAllocationY;
        adjustedSpaceX = (availableHeight * aspectRatio) / windowWidth;
        adjustedPivotX = pivotX + (spaceAllocationX - adjustedSpaceX) / 2.0;
        adjustedPivotY = pivotY;
    } else {
        // Высота слишком большая, уменьшаем высоту
        adjustedSpaceX = spaceAllocationX;
        adjustedSpaceY = (availableWidth / aspectRatio) / windowHeight;
        adjustedPivotX = pivotX;
        adjustedPivotY = pivotY + (spaceAllocationY - adjustedSpaceY) / 2.0;
    }
}

void AspectRatioWrapper::draw() {
    if (object) object->draw();
}

void AspectRatioWrapper::resize() {
    recalculateDimensions();

    if (object) {
        object->setAllocationX(adjustedSpaceX);
        object->setAllocationY(adjustedSpaceY);
        object->setPivotX(adjustedPivotX);
        object->setPivotY(adjustedPivotY);
        object->resize();
    }
}

void AspectRatioWrapper::setPivotX(double val) {
    pivotX = val;
    recalculateDimensions();
    if (object) object->setPivotX(adjustedPivotX);
}

void AspectRatioWrapper::setPivotY(double val) {
    pivotY = val;
    recalculateDimensions();
    if (object) object->setPivotY(adjustedPivotY);
}

void AspectRatioWrapper::setAllocationX(double val) {
    spaceAllocationX = val;
    recalculateDimensions();
    if (object) object->setAllocationX(adjustedSpaceX);
}

void AspectRatioWrapper::setAllocationY(double val) {
    spaceAllocationY = val;
    recalculateDimensions();
    if (object) object->setAllocationY(adjustedSpaceY);
}
