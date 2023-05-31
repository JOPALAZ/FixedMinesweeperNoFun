#pragma once
#include <SFML/Graphics.hpp>
#include"constants.h"
#include<map>
#include"SmartArray.h"
#include<fstream>
class Menu
{
public:
	Menu();
	void draw(sf::RenderWindow* win);
	std::string leftClick(sf::RenderWindow* win);
	bool isOk() { return isOK; }
private:
	bool isOK = true;
	float scaleSOADY=1;
	float scaleSOADX=1;
	float scaleSlipY=1;
	float scaleSlipX=1;
	float allocatedSpaceForArmenians = 0.25f;
	sf::Texture textureSOAD;
	sf::Sprite SystemOfADown;
	sf::Font font;
	sf::Text title;
	sf::Text menuText;
	unsigned titleSize = 1;
	sf::Texture textureSlipknot;
	sf::Sprite Slipknot;
	std::map<sf::Text*, sf::RectangleShape*> Buttons;
};

