#pragma once
#include "constants.h"
#include "DrawableObject.h"
#include <SFML/Graphics.hpp>
#include <vector>
class SoundHandler;

struct ObjectCollection {
  std::vector<baseDrawableObject *> drawObjects;
  std::vector<baseInteractiveDrawableObject *> interactiveObjects;
};

class SceneHandler {
  ObjectCollection *scene;
  sf::RenderWindow *window;
  SoundHandler *soundHandler;
  void exitAll() { window->close(); }
  void unloadScene() {
    if (scene) {
      for (baseDrawableObject *el : scene->drawObjects) {
        if (el) {
          delete el;
          el = nullptr;
        }
      }
      delete scene;
      scene = nullptr;
    }
    if (soundHandler) {
      delete soundHandler;
      soundHandler = nullptr;
    }
  }

public:
  SceneHandler(sf::RenderWindow *window) {
    this->window = window;
    soundHandler = nullptr;
    scene = nullptr;
  }
  SceneHandler() = default;
  void takeSignal(Signal sig) {
    switch (sig) {
    case LOAD_GAME:
      unloadScene();
      break;
    case LOAD_MENU:
      unloadScene();
      break;
    case UNLOAD:
      unloadScene();
      break;
    default:
      break;
    }
  }
  void takeSignal(std::string sig) {
    if (sig == "LoadGameTetris") {
      unloadScene();
    } else if (sig == "LoadMenu") {
      unloadScene();
    } else if (sig == "Exit") {
      unloadScene();
      exitAll();
    } else if (sig == "Unload") {
      unloadScene();
    }
  }
  ObjectCollection *getScene() { return scene; }
};