#include "SceneHandler.h"
#include "VerticalDrawableSplitter.h"
#include "HorizontalDrawableSplitter.h"
#include "VerticalDrawableSplitter.h"
#include "InteractiveButton.h"
void SceneHandler::exitAll() {
  window->close();
}

void SceneHandler::unloadScene(bool deleteSound) {
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
  if (soundHandler&&deleteSound) {
    delete soundHandler;
    soundHandler = nullptr;
  }
}

SceneHandler::SceneHandler(sf::RenderWindow *window) {
  this->window = window;
  soundHandler = nullptr;
  scene = nullptr;
}

void SceneHandler::loadGame(std::string pathParam)
{
 InteractiveButton* button1 = new InteractiveButton
 ("test1","testSig",this,0,0,1.0,1.0,this->window);
  InteractiveButton* button2 = new InteractiveButton
 ("test2","testSig",this,0,0,1.0,1.0,this->window);
  InteractiveButton* button3 = new InteractiveButton
 ("test3","testSig",this,0,0,1.0,1.0,this->window);
  InteractiveButton* button4 = new InteractiveButton
 ("test4","testSig",this,0,0,1.0,1.0,this->window);
 verticalDrawableSplitter* vert = new verticalDrawableSplitter(0.5);
 horizontalDrawableSplitter* hor1 = new horizontalDrawableSplitter
 (0.5,button1,button2,1,1,0,0);
 horizontalDrawableSplitter* hor2 = new horizontalDrawableSplitter
 (0.5,button3,button4,1,1,0,0);
 vert->addObj(hor1);
 vert->addObj(hor2);
 vert->resize();
    this->scene = new ObjectCollection;
    scene->drawObjects.push_back(vert);
}

SceneHandler::SceneHandler()
    : window(nullptr), soundHandler(nullptr), scene(nullptr) {}

void SceneHandler::takeSignal(std::string sig, std::string params) {
  if (sig == "LoadGameTetris") {
    unloadScene(false);
  } else if (sig == "LoadMenu") {
    unloadScene(false);
  } else if (sig == "Exit") {
    unloadScene(true);
    exitAll();
  } else if (sig == "Unload") {
    unloadScene(false);
  }
}

ObjectCollection *SceneHandler::getScene() {
  return scene;
}
