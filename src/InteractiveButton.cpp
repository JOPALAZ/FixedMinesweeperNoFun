#include "InteractiveButton.h"

InteractiveButton::InteractiveButton(
    const std::string& textString, const std::string& signal, SceneHandler* handler,
    double pivotX, double pivotY, double spaceAllocationX, double spaceAllocationY,
    sf::RenderWindow* window)
{
    this->textString = textString;
    this->signal = signal;
    this->handler = handler;
    this->pivotX = pivotX;
    this->pivotY = pivotY;
    this->spaceAllocationX = spaceAllocationX;
    this->spaceAllocationY = spaceAllocationY;
    this->window = window;

    if (!font.loadFromFile("resources/Font.TTF")) {
        throw std::runtime_error("Cannot load necessary game data.");
    }

    text.setFont(font);
    text.setString(textString);
    text.setFillColor(sf::Color::Black);

    rectangle.setFillColor(sf::Color::White);
}

void InteractiveButton::draw() {
    window->draw(rectangle);
    window->draw(text);
}

void InteractiveButton::resize() {
    double windowWidth = window->getSize().x;
    double windowHeight = window->getSize().y;

    double totalPaddingX = spaceAllocationX * padding * windowWidth * 2.0;
    double totalPaddingY = spaceAllocationY * padding * windowHeight * 2.0;

    usefulSpaceX = (spaceAllocationX * windowWidth) - totalPaddingX;
    usefulSpaceY = (spaceAllocationY * windowHeight) - totalPaddingY;

    rectangle.setSize(sf::Vector2f(static_cast<float>(usefulSpaceX), static_cast<float>(usefulSpaceY)));
    rectangle.setOrigin(usefulSpaceX / 2.0f, usefulSpaceY / 2.0f);

    sf::FloatRect textBounds = text.getLocalBounds();
    float scaleX = usefulSpaceX / textBounds.width;
    float scaleY = usefulSpaceY / textBounds.height;
    float scale = std::min(scaleX, scaleY) * 0.8f;

    text.setCharacterSize(static_cast<unsigned int>(200));
    text.setScale(scale, scale);

    textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                   textBounds.top + textBounds.height / 2.0f);

    sf::Vector2f position(
        static_cast<float>((pivotX + spaceAllocationX / 2.0) * windowWidth),
        static_cast<float>((pivotY + spaceAllocationY / 2.0) * windowHeight)
    );

    rectangle.setPosition(position);
    text.setPosition(position);
}

int InteractiveButton::processMouse() {
    handler->takeSignal(signal, "");
    return -1;
}

void InteractiveButton::processInput() {
    handler->takeSignal(signal, "");
}
