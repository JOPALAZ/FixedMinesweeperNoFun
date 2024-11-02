#include "DrawableObject.h"

class AspectRatioWrapper : public baseDrawableObject {
public:
    AspectRatioWrapper(baseDrawableObject* object, double aspectRatio,
                       double spaceX = 1.0, double spaceY = 1.0,
                       double pivotX = 0.0, double pivotY = 0.0,
                       sf::RenderWindow* window = nullptr);

    void draw() override;
    void resize() override;

    void setPivotX(double val) override;
    void setPivotY(double val) override;
    void setAllocationX(double val) override;
    void setAllocationY(double val) override;

    ~AspectRatioWrapper();

private:
    void recalculateDimensions();

    baseDrawableObject* object = nullptr;
    double aspectRatio = 1.0;

    double adjustedPivotX = 0.0;
    double adjustedPivotY = 0.0;
    double adjustedSpaceX = 0.0;
    double adjustedSpaceY = 0.0;

    sf::RenderWindow* window = nullptr;
};
