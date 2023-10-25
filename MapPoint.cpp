#include "MapPoint.h"
MapPoint::MapPoint() {
  number = 0;
  textures = nullptr;
};

MapPoint::MapPoint(int num, std::map<std::string, sf::Texture *> *textures)
    : textures(textures) {
  opened = false;
  number = num;
}
bool MapPoint::step() {
  opened = true;

  body.setTexture(*textures->at("N" + std::to_string(number)), true);
  setSize(sizeX, sizeY);
  if (number == -1)
    return 0;
  return 1;
};
char MapPoint::flag() {
  if (!opened) {
    if (flagged) {
      if (!sure) {
        sure = true;
        flagged = false;
        body.setTexture(*textures->at("UNKNOWN"), true);
        setSize(sizeX, sizeY);
        return -1;
      }
      sure = false;
      body.setTexture(*textures->at("QUESTIONUS"), true);
      setSize(sizeX, sizeY);
      return 0;
    }
    flagged = true;
    body.setTexture(*textures->at("QUESTION"), true);
    setSize(sizeX, sizeY);
    return 1;
  }
  return 0;
}
int MapPoint::getNum() { return number; }
void MapPoint::setNum(int num) { number = num; }
bool MapPoint::isntOpened() { return !opened; }
void MapPoint::setTextures(std::map<std::string, sf::Texture *> *texturesIn) {
  textures = texturesIn;

  body.setTexture(*textures->at("UNKNOWN"), true);
}
void MapPoint::setSize(float x, float y) {
  float scaleX = sizeX / body.getTexture()->getSize().x;
  float scaleY = sizeY / body.getTexture()->getSize().y;
  body.setScale(scaleX, scaleY);
}
void MapPoint::setCellSizes(float x, float y) {
  sizeX = x;
  sizeY = y;
}
void MapPoint::setPosition(float x, float y) {
  body.setPosition(sf::Vector2f(x, y));
}
sf::Sprite MapPoint::getSprite() { return body; }
char MapPoint::unflag() {
  if (flagged) {
    flagged = false;
    sure = true;
    body.setTexture(*textures->at("UNKNOWN"), true);
    return -1;
  }
  flagged = false;
  sure = true;
  return 0;
}