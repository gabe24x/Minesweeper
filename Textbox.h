#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#pragma once

class Textbox {
public:
    Textbox();
    void setFont(sf::Font &font);
    void setPosition(sf::Vector2f pos);
    std::string getText();
    void drawTo(sf::RenderWindow &window);
    void typedOn(sf::Event input, std::string& userName);
private:
    sf::Text textbox;
    std::ostringstream text;
    float x_pos;
    float y_pos;
    void inputLogic(int charTyped);
    void deleteLastChar();
};
