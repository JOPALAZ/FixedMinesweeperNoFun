
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "GameField.h"
#include <random>
#include <cmath>
#include <string>
#include<fstream>


int main()
{
    GameField gameField;
    if(!gameField.isOk()){
        std::cout << "NOT ALL FILES WERE LOADED\n";
        return -1;
    }
    sf::RenderWindow* window=new sf::RenderWindow(sf::VideoMode(WINDOW_RES.first, WINDOW_RES.second), "Minesweeper");
    window->setSize(sf::Vector2u(WINDOW_RES.first, WINDOW_RES.second));


    window->setFramerateLimit(60); 
   
    while (window->isOpen())
    {
      
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    try {
                        gameField.leftClickOnField(window);
                    }
                    catch (std::exception& ex) {
                        std::cout << "RUNTIME ERROR: " << ex.what();
                        return -1;
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) 
                {
                    gameField.rightClickOnField(window);

                }
                

            }
            if (event.type == sf::Event::KeyReleased) 
            {
                if (event.key.code == sf::Keyboard::M) 
                {
                    gameField.mute();
                }
                else if (event.key.shift && event.key.code == sf::Keyboard::H)
                {
                    gameField.superHint(window);
                }
                else if (event.key.code == sf::Keyboard::H) 
                {
                    gameField.hint(window);
                }
            }
        }

        window->clear();
        gameField.drawAllElements(window);
        window->display();
    }

    return 0;
}
