#pragma once

#include "constants.h"
#include "DrawableObject.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class SoundHandler;

struct ObjectCollection {
  std::vector<baseDrawableObject *> drawObjects;
  std::vector<baseInteractiveDrawableObject *> interactiveObjects;
};

class SceneHandler {
private:
  ObjectCollection *scene;
  sf::RenderWindow *window;
  SoundHandler *soundHandler;

  void exitAll();
  void unloadScene(bool deleteSound);

public:
  SceneHandler(sf::RenderWindow *window);
  void loadGame(std::string pathParam);
  SceneHandler();
  void takeSignal(std::string sig, std::string params);
  ObjectCollection *getScene();
};
