#include "menu.h"
#include<filesystem>
std::string clean(const std::string& str) 
{
	std::string result;
	bool started = false;
    for (const auto& c : str)
    {
        if (std::isalnum(c) || (c ==' ' && started))
        {
            result += c;
			started = true;
        }
    }
    return result;
}
Menu::Menu() {
	std::filesystem::path menuPath = std::filesystem::current_path();
	if (!font.loadFromFile((menuPath/"Font.TTF").generic_string())) { isOK = false; return; }
	if (!textureSlipknot.loadFromFile((menuPath / "title_pic1.png").generic_string())) {  isOK = false; return; }
	if (!textureSOAD.loadFromFile((menuPath / "title_pic0.png").generic_string())) {  isOK = false; return; }
	textureSOAD.setSmooth(true);
	title_picture0.setTexture(textureSOAD, true);
	scaleSOADY = (WINDOW_RES.second * allocatedSpaceForArmenians) / textureSOAD.getSize().y;
	scaleSOADX = scaleSOADY;
	title_picture0.setScale(scaleSOADX, scaleSOADY);
	title_picture0.setOrigin(0, title_picture0.getTexture()->getSize().y / 2.f);
	title_picture0.setPosition(0 - title_picture0.getTexture()->getSize().x * scaleSOADX,
		WINDOW_RES.second - textureSOAD.getSize().y * scaleSOADY / 2.f);

	
	textureSlipknot.setSmooth(true);
	title_picture1.setTexture(textureSlipknot, true);
	scaleSlipY = (WINDOW_RES.second * allocatedSpaceForArmenians) / textureSlipknot.getSize().y;
	scaleSlipX = title_picture0.getTexture()->getSize().x * scaleSOADX / title_picture1.getTexture()->getSize().x;	
	title_picture1.setScale(scaleSlipX, scaleSlipY);
	title_picture1.setOrigin(0, title_picture1.getTexture()->getSize().y / 2.f);
	title_picture1.setPosition((float)title_picture0.getPosition().x - (float)WINDOW_RES.first,
		WINDOW_RES.second - textureSlipknot.getSize().y * scaleSlipY / 2.f);
	title.setString("MINESWEEPER");
	title.setFont(font);
	title.setCharacterSize(100);
	title.setFillColor(sf::Color::White);
	float scale = std::min(WINDOW_RES.second * allocatedSpaceForArmenians * 0.75f / title.getLocalBounds().height, (-1.f * title_picture1.getPosition().x - 2 * title_picture1.getGlobalBounds().width) / title.getLocalBounds().width);
	title.setScale(scale, scale);
	title.setOrigin(title.getLocalBounds().left + title.getLocalBounds().width/2.f, title.getLocalBounds().top + title.getLocalBounds().height / 2.f);
	title.setPosition(float(2*WINDOW_RES.first),
		float(WINDOW_RES.second - textureSlipknot.getSize().y * scaleSlipY / 2.f));
	
	menuText.setFont(font);
	menuText.setCharacterSize(100);
	menuText.setScale(scale, scale);
	menuText.setFillColor(sf::Color::White);
	menuText.setString("MENU");
	menuText.setOrigin(menuText.getLocalBounds().left + menuText.getLocalBounds().width / 2.f, menuText.getLocalBounds().top + menuText.getLocalBounds().height / 2.f);
	menuText.setPosition(-1.f*WINDOW_RES.first/2.F-textureSlipknot.getSize().x*scaleSlipX/2.f,WINDOW_RES.second - textureSlipknot.getSize().y * scaleSlipY / 2.f);


	sf::Text* text;
	sf::RectangleShape* rect;
	std::ifstream levelNames;
	levelNames.open(menuPath / "levelnames.txt");
	if (levelNames.fail())
	{
		std::cout << "FAILED TO OPEN LEVELNAMES FILE\n";
		this->isOK = false;
	}
	std::string line;
	SmartArray<std::string> Levels;
	while (std::getline(levelNames, line)&&clean(line).size())
	{
		Levels.push_back(clean(line));
	}
	
	levelNames.close();
	float sizeOfAButtonX = WINDOW_RES.first - DISTANCE_BETWEEN_BUTTONS * 2;
	float sizeOfAButtonY = (WINDOW_RES.second * (1 - allocatedSpaceForArmenians) - DISTANCE_BETWEEN_BUTTONS * 2) 
		/ Levels.getSize()- DISTANCE_BETWEEN_BUTTONS;
	for (unsigned buttonIndex{}; buttonIndex < Levels.getSize(); buttonIndex++)
	{
		std::string str = Levels[buttonIndex];
		unsigned char_size = 200;
		text = new sf::Text;
		text->setString(str);
		text->setFont(font);
		text->setCharacterSize(char_size);
		rect = new sf::RectangleShape;
		rect->setFillColor(sf::Color::White);
		rect->setSize(sf::Vector2f(sizeOfAButtonX, sizeOfAButtonY));
		rect->setOrigin(rect->getGlobalBounds().width / 2.f + rect->getGlobalBounds().left, rect->getGlobalBounds().height / 2.f + rect->getGlobalBounds().top);
		rect->setPosition(float(WINDOW_RES.first / 2),
			float(buttonIndex * (sizeOfAButtonY + DISTANCE_BETWEEN_BUTTONS) + DISTANCE_BETWEEN_BUTTONS + sizeOfAButtonY / 2));
		float scale = ((rect->getLocalBounds().height / 1.5f) / text->getLocalBounds().height);

		text->setScale(scale,scale);
		text->setFillColor(sf::Color::Black);
		text->setOrigin((text->getGlobalBounds().width / 2.f + text->getGlobalBounds().left)/scale, (text->getGlobalBounds().height / 2.f + text->getGlobalBounds().top)/scale);
		text->setPosition(float(WINDOW_RES.first / 2),
			float(buttonIndex * (sizeOfAButtonY + DISTANCE_BETWEEN_BUTTONS) + DISTANCE_BETWEEN_BUTTONS + sizeOfAButtonY / 2));
		if (text->getGlobalBounds().width >= rect->getGlobalBounds().width) {
			scale = ((rect->getLocalBounds().width / 1.5f) / text->getLocalBounds().width);
			text->setScale(scale, scale);
		}
		//text->setPosition(rect->getGlobalBounds().left + rect->getGlobalBounds().width / 2 - text->getLocalBounds().width / 2,
			//rect->getGlobalBounds().top + rect->getGlobalBounds().height / 2 - text->getLocalBounds().height / 2-DISTANCE_BETWEEN_BUTTONS);
		Buttons[text] = rect;
		//buttonIndex++;
		
		
	}
	rect = nullptr;
	text = nullptr;

}

void Menu::draw(sf::RenderWindow* win) {
	win->draw(title_picture0);
	win->draw(title_picture1);
	win->draw(title);
	win->draw(menuText);
	if (title_picture0.getPosition().x<= WINDOW_RES.first&& title_picture1.getPosition().x <= WINDOW_RES.first)
	{
		
		title_picture0.setPosition(title_picture0.getPosition() + sf::Vector2f(animationSpeed, 0));
		title_picture1.setPosition(title_picture1.getPosition() + sf::Vector2f(animationSpeed, 0));
		title.setPosition(title.getPosition() + sf::Vector2f(animationSpeed, 0));
		menuText.setPosition(menuText.getPosition() + sf::Vector2f(animationSpeed, 0));
	}
	else if (title_picture0.getPosition().x <= WINDOW_RES.first)
	{
		title_picture1.setPosition((float)title_picture0.getPosition().x - (float)WINDOW_RES.first,
			title_picture1.getPosition().y);
		
		title_picture0.setPosition(title_picture0.getPosition() + sf::Vector2f(animationSpeed, 0));

		title.setPosition(title.getPosition() + sf::Vector2f(animationSpeed, 0));
		menuText.setPosition(title.getPosition().x - WINDOW_RES.first,
			WINDOW_RES.second - textureSlipknot.getSize().y * scaleSlipY / 2.f);
	}
	else if (title_picture1.getPosition().x <= WINDOW_RES.first) {
		title_picture0.setPosition((float)title_picture1.getPosition().x - (float)WINDOW_RES.first,
			title_picture0.getPosition().y);
		menuText.setPosition(menuText.getPosition() + sf::Vector2f(animationSpeed, 0));
		title_picture1.setPosition(title_picture1.getPosition() + sf::Vector2f(animationSpeed, 0));
		title.setPosition((title_picture1.getPosition().x + title_picture1.getGlobalBounds().width + title_picture0.getPosition().x) / 2.f,
			WINDOW_RES.second - textureSlipknot.getSize().y * scaleSlipY / 2.f);

	}
	for (const std::pair<sf::Text*,sf::RectangleShape*>& i : Buttons) {
	
		win->draw(*i.second);
		win->draw(*i.first);
	}
	
	
}
std::string Menu::leftClick(sf::RenderWindow* win)
{
	sf::Vector2i pos = sf::Mouse::getPosition(*win);
	sf::Vector2f casted = static_cast<sf::Vector2f>(pos); 
	for(std::pair<sf::Text*,sf::RectangleShape*> button : Buttons)
	{
		if (button.second->getGlobalBounds().contains(casted)) {
			return button.first->getString();
		}
	}
	return "";
}
