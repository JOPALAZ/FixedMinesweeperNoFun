#include "GameField.h"
#include <filesystem>
#include <fstream>
GameField::GameField() { isOK = menu.isOk(); }
std::map<std::string, sf::Texture *> *
GameField::LoadTextures(std::filesystem::path path) {
  if (textures != nullptr) {
    for (auto &k : *textures) {
      if (k.second != nullptr) {
        k.second->~Texture();
        k.second = nullptr;
      }
    }
    textures->clear();
    delete textures;
    textures = nullptr;
  }
  sf::Texture *buf = new sf::Texture;
  std::map<std::string, sf::Texture *> *exhaust =
      new std::map<std::string, sf::Texture *>;
  for (short i{-1}; i < 9; ++i) {
    if (!buf->loadFromFile(
            path.append("N" + std::to_string(i) + ".png").generic_string())) {
      std::string exception_text = "DIDN'T FIND " + path.generic_string();
      throw std::invalid_argument(exception_text);
    }
    path = path.parent_path();
    exhaust->insert(std::make_pair("N" + std::to_string(i), buf));
    buf = nullptr;
    buf = new sf::Texture;
  }
  if (!buf->loadFromFile(path.append("UNKNOWN.png").generic_string())) {
    std::string exception_text = "DIDN'T FIND " + path.generic_string();
    throw std::invalid_argument(exception_text);
  }
  path = path.parent_path();
  exhaust->insert(std::make_pair("UNKNOWN", buf));
  buf = nullptr;
  buf = new sf::Texture;
  if (!buf->loadFromFile(path.append("QUESTION.png").generic_string())) {
    std::string exception_text = "DIDN'T FIND " + path.generic_string();
    throw std::invalid_argument(exception_text);
  }
  path = path.parent_path();
  exhaust->insert(std::make_pair("QUESTION", buf));
  buf = nullptr;
  buf = new sf::Texture;
  if (!buf->loadFromFile(path.append("QUESTIONUS.png").generic_string())) {
    std::string exception_text = "DIDN'T FIND " + path.generic_string();
    throw std::invalid_argument(exception_text);
  }
  path = path.parent_path();
  exhaust->insert(std::make_pair("QUESTIONUS", buf));
  buf = nullptr;
  return exhaust;
}
void GameField::mute() {
  if (SoundTrack.getVolume() != 0.f) {
    volume = SoundTrack.getVolume();
    SoundTrack.setVolume(0.f);
    muted = true;
  } else {
    SoundTrack.setVolume(volume);
    muted = false;
  }
  if (WinLoseSound.getStatus() == sf::Sound::Playing) {
    WinLoseSound.setVolume([&]() -> float {
      if (muted)
        return 0.f;
      if (volume != 0.f)
        return volume;
      else
        return 50.f;
    }());
  }
}
void GameField::loadSoundTrack() {
  unloadSoundTrack();

  std::filesystem::path soundpath = path;
  soundpath.append("soundtrack");
  if (!SoundTrack.openFromFile(soundpath.generic_string())) {

    throw std::runtime_error("THERE IS NO " + soundpath.generic_string());
  }
  SoundTrack.setLoop(true);
  SoundTrack.setVolume(50.f);
  volume = SoundTrack.getVolume();
  if (muted)
    SoundTrack.setVolume(0.f);
  SoundTrack.play();
}
void GameField::unloadSoundTrack() {
  if (SoundTrack.getStatus() == sf::Sound::Playing)
    SoundTrack.stop();
  if (WinLoseSound.getStatus() == sf::Sound::Playing)
    WinLoseSound.stop();
}
bool GameField::MakeGameField(std::filesystem::path path, int difficulty) {

  if (!headerTexture.loadFromFile(path.append("header.png").generic_string())) {
    isOK = false;
    std::cout << "Not all textures were loaded \n";
    return false;
  }
  try {
    textures = LoadTextures(path.parent_path());
  } catch (const std::exception &) {
    isOK = false;
    std::cout << "Not all textures were loaded \n";
    return false;
  }
  header.setTexture(headerTexture, true);
  header.setPosition(sf::Vector2f(0, 0));
  scaleX = WINDOW_RES.first / (float)header.getTexture()->getSize().x * 0.6f;
  scaleY =
      (WINDOW_RES.second * MARGIN_SCALE) / header.getTexture()->getSize().y;
  header.setScale(scaleX, scaleY);
  float minefieldScaleX, minefieldScaleY;
  if (WINDOW_RES.first > WINDOW_RES.second) {
    minefieldScaleX = 1.f;
    minefieldScaleY =
        WINDOW_RES.second * (1.f - MARGIN_SCALE) / (float)WINDOW_RES.first;
  } else {
    minefieldScaleY = 1.f;
    minefieldScaleX =
        WINDOW_RES.first / (float)WINDOW_RES.second / (1.f - MARGIN_SCALE);
  }
  gameMap.deleteUnique();
  gameMap.create(
      MapSize(difficulty * minefieldScaleY),
      MapSize(difficulty * minefieldScaleX), textures,
      std::make_pair((unsigned short)(WINDOW_RES.second * MARGIN_SCALE), 0));
  if (!Font.loadFromFile(
          (std::filesystem::current_path() / "Font.TTF").generic_string())) {
    std::cout << "FONT WASN'T LOADED\n";
    isOK = false;
    return false;
  }
  bombAmount.setFont(Font);
  screenSpaceAllocatedForText =
      unsigned(WINDOW_RES.first - headerTexture.getSize().x * scaleX);
  bombAmountString = "BOMBS LEFT: " + std::to_string(gameMap.getBombAmount());
  bombAmount.setString(bombAmountString);
  this->charSizeHeight = 72;
  bombAmount.setCharacterSize(this->charSizeHeight);
  float scale =
      std::min((WINDOW_RES.first * 0.32f) / bombAmount.getLocalBounds().width,
               (WINDOW_RES.first * MARGIN_SCALE * 0.8f) /
                   bombAmount.getLocalBounds().height);
  bombAmount.setScale(scale, scale);
  // while (bombAmount.getLocalBounds().width <= WINDOW_RES.first * 0.32f &&
  // bombAmount.getLocalBounds().height <= WINDOW_RES.first * MARGIN_SCALE *
  // 0.8f)
  //{
  //     charSizeHeight++;
  //     bombAmount.setCharacterSize(charSizeHeight);
  // }
  // while (bombAmount.getLocalBounds().width > WINDOW_RES.first * 0.32f ||
  // bombAmount.getLocalBounds().height > WINDOW_RES.first * MARGIN_SCALE *
  // 0.8f)
  //{
  //     charSizeHeight--;
  //     bombAmount.setCharacterSize(charSizeHeight);
  // }

  bombAmount.setOrigin(bombAmount.getLocalBounds().left +
                           bombAmount.getLocalBounds().width / 2.0f,
                       bombAmount.getLocalBounds().top +
                           bombAmount.getLocalBounds().height / 2.0f);
  bombAmount.setPosition(WINDOW_RES.first * 0.8f,
                         WINDOW_RES.second * MARGIN_SCALE / 2.f);
  bombAmount.setFillColor(sf::Color::White);
  try {
    loadSoundTrack();
  } catch (std::exception &ex) {
    this->isOK = false;
    std::cout << "EXCEPTION: " << ex.what();
    return false;
  }
  gameIsOn = true;
  return true;
}
void GameField::drawAllElements(sf::RenderWindow *window) {
  if (draw) {
    if (gameIsOn) {

      bombAmount.setString(bombAmountString);
      window->draw(header);
      window->draw(bombAmount);
      gameMap.drawMap(window);

    } else if (drawGameMenu) {
      menu.draw(window);
    }
  }
}
bool GameField::leftClickOnField(sf::RenderWindow *window) {

  if (gameIsOn) {
    int x = sf::Mouse::getPosition(*window).x;
    int y = sf::Mouse::getPosition(*window).y;
    if (!gameMap.leftClickOnMap(x, y)) {

      bombAmountString = "YOU LOST";
      bombAmount.setString(bombAmountString);
      float scale = std::min((WINDOW_RES.first * 0.32f) /
                                 bombAmount.getLocalBounds().width,
                             (WINDOW_RES.first * MARGIN_SCALE * 0.8f) /
                                 bombAmount.getLocalBounds().height);
      bombAmount.setScale(scale, scale);

      bombAmount.setOrigin(bombAmount.getLocalBounds().left +
                               bombAmount.getLocalBounds().width / 2.0f,
                           bombAmount.getLocalBounds().top +
                               bombAmount.getLocalBounds().height / 2.0f);
      bombAmount.setPosition(WINDOW_RES.first * 0.8f,
                             WINDOW_RES.second * MARGIN_SCALE / 2.f);
      bombAmount.setFillColor(sf::Color(255, 64, 48)); // Brown color
      gameMap.openAllMap();
      window->clear();
      drawAllElements(window);
      window->display();
      playWinLooseSound(false);
      gameIsOn = false;
      gameMap.deleteUnique();
      return false;
    }
    if (isWin(window))
      return true;
    bombAmountString = "BOMBS LEFT: " + std::to_string(gameMap.getBombAmount());
    return true;
  } else {
    std::string levelname = menu.leftClick(window);
    this->path = std::filesystem::current_path().append(levelname);
    if (levelname.size() != 0) {
      if (!MakeGameField(this->path, getDifficulty()))
        throw std::runtime_error("NOT ALL FILES WERE LOADED");
    }
  }
  return false;
}
bool GameField::isWin(sf::RenderWindow *window) {
  if (gameMap.checkWinState()) {
    bombAmountString = "YOU WON";
    bombAmount.setString(bombAmountString);
    float scale =
        std::min((WINDOW_RES.first * 0.32f) / bombAmount.getLocalBounds().width,
                 (WINDOW_RES.first * MARGIN_SCALE * 0.8f) /
                     bombAmount.getLocalBounds().height);
    bombAmount.setScale(scale, scale);
    bombAmount.setOrigin(bombAmount.getLocalBounds().left +
                             bombAmount.getLocalBounds().width / 2.0f,
                         bombAmount.getLocalBounds().top +
                             bombAmount.getLocalBounds().height / 2.0f);
    bombAmount.setPosition(WINDOW_RES.first * 0.8f,
                           WINDOW_RES.second * MARGIN_SCALE / 2.f);
    bombAmount.setFillColor(sf::Color(9, 121, 105)); // ZELENIY
    gameMap.openAllMap();
    window->clear();
    drawAllElements(window);
    window->display();
    playWinLooseSound(true);
    gameIsOn = false;
    gameMap.deleteUnique();
    return true;
  }
  return false;
}

unsigned GameField::getDifficulty() {
  std::filesystem::path difficultyPath = path;
  std::ifstream file(difficultyPath.append("dif").generic_string());
  unsigned difficulty;
  if (file.is_open()) {
    file >> difficulty;
  } else
    difficulty = 30;
  return difficulty;
}
void GameField::playWinLooseSound(bool win) {
  unloadSoundTrack();
  sf::sleep(sf::milliseconds(250));
  if (win) {
    WinLoseSound.openFromFile(
        (std::filesystem::current_path() / "win.flac").generic_string());
  } else {
    WinLoseSound.openFromFile(
        (std::filesystem::current_path() / "lose.flac").generic_string());
  }
  WinLoseSound.setVolume([&]() -> float {
    if (muted)
      return 0.f;
    if (volume != 0.f)
      return volume;
    else
      return 50.f;
  }());
  WinLoseSound.setLoop(false);
  WinLoseSound.play();

  sf::sleep(sf::seconds(3));
}
void GameField::rightClickOnField(sf::RenderWindow *window) {
  if (gameIsOn) {
    int x = sf::Mouse::getPosition(*window).x;
    int y = sf::Mouse::getPosition(*window).y;
    gameMap.rightClickOnMap(x, y);
    if (gameMap.getBombAmount() == 0) {
      if (gameMap.checkWinState()) {
        bombAmountString = "YOU WON";
        bombAmount.setString(bombAmountString);
        float scale = std::min((WINDOW_RES.first * 0.32f) /
                                   bombAmount.getLocalBounds().width,
                               (WINDOW_RES.first * MARGIN_SCALE * 0.8f) /
                                   bombAmount.getLocalBounds().height);
        bombAmount.setScale(scale, scale);

        bombAmount.setOrigin(bombAmount.getLocalBounds().left +
                                 bombAmount.getLocalBounds().width / 2.0f,
                             bombAmount.getLocalBounds().top +
                                 bombAmount.getLocalBounds().height / 2.0f);
        bombAmount.setPosition(WINDOW_RES.first * 0.8f,
                               WINDOW_RES.second * MARGIN_SCALE / 2.f);
        bombAmount.setFillColor(sf::Color(9, 121, 105)); // ZELENIY
        gameMap.openAllMap();
        window->clear();
        drawAllElements(window);
        window->display();
        playWinLooseSound(true);
        gameIsOn = false;
        gameMap.deleteUnique();
        return;
      }
    }
    bombAmountString = "BOMBS LEFT: " + std::to_string(gameMap.getBombAmount());
  }
}
void GameField::drawMenu(sf::RenderWindow *window) { menu.draw(window); }
void GameField::wait(unsigned msec) { sf::sleep(sf::milliseconds(msec)); }

GameField::~GameField() {
  if (textures != nullptr) {
    for (auto &k : *textures) {
      if (k.second != nullptr) {
        k.second->~Texture();
        k.second = nullptr;
      }
    }
    textures->clear();
    delete textures;
    textures = nullptr;
  }
}