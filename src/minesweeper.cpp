
//#include "GameField.h"
#include "SceneHandler.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

int main() {


  
  sf::RenderWindow window(sf::VideoMode(400, 400), "ARCADE AHAHA");
  SceneHandler scene(&window);
  scene.loadGame("dsa");
  window.setVerticalSyncEnabled(true);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::Resized) {
        sf::View view;
        view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
        window.setView(view);
        for (const auto &el : scene.getScene()->drawObjects) {
          el->resize();
        }
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Button::Left &&
            scene.getScene()) {
          for (const auto &el : scene.getScene()->interactiveObjects) {
            if (el && el->mouseInBounds()) {
              el->processMouse();
            }
            if (!scene.getScene()) {
              break;
            }
          }
        }
      }
      if (event.type == sf::Event::KeyPressed && scene.getScene()) {
        for (const auto &el : scene.getScene()->interactiveObjects) {
          if (el->takesInput()) {
            el->processInput();
          }
        }
      }
    }

    window.clear();
    if (scene.getScene()) {
      for (const auto &el : scene.getScene()->drawObjects) {
        el->draw();
      }
    }
    window.display();
  }

  return 0;
  /*GameField gameField;
  if (!gameField.isOk()) {
    std::cout << "NOT ALL FILES WERE LOADED\n";
    return -1;
  }
  sf::RenderWindow *window = new sf::RenderWindow(
      sf::VideoMode(WINDOW_RES.first, WINDOW_RES.second), "Minesweeper");
  window->setSize(sf::Vector2u(WINDOW_RES.first, WINDOW_RES.second));

  window->setFramerateLimit(60);

  while (window->isOpen()) {

    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window->close();
      if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          try {
            gameField.leftClickOnField(window);
          } catch (std::exception &ex) {
            std::cout << "RUNTIME ERROR: " << ex.what();
            return -1;
          }
        } else if (event.mouseButton.button == sf::Mouse::Right) {
          gameField.rightClickOnField(window);
        }
      }
      if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::M) {
          gameField.mute();
        } else if (event.key.shift && event.key.code == sf::Keyboard::H) {
          gameField.superHint(window);
        } else if (event.key.code == sf::Keyboard::H) {
          gameField.hint(window);
        }
      }
    }

    window->clear();
    gameField.drawAllElements(window);
    window->display();
  }

  return 0;
  */
}
