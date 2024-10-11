#pragma once
#include <iostream>
#include <vector>
const float MARGIN_SCALE = 0.1666667f;
// std::vector<std::string>* Levels;
const float padding = 0.05f;
const std::pair<int, int> WINDOW_RES(1600, 900);
const float DISTANCE_BETWEEN_BUTTONS = 20.f;
const unsigned animationSpeed = 3;
const float marginFromHeader = 0.05f;
enum Signal
{
    LOAD_GAME,
    LOAD_MENU,
    UNLOAD,
};