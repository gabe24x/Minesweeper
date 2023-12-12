#include <SFML/Graphics.hpp>
#include <vector>
#include "TextureManager.h"
#include <iostream>
#pragma once

class Button {
public:
    Button(int num, int rowCount, int colCount);
    bool Click(sf::Event& event, sf::RenderWindow& gameWindow);
    void Draw(sf::RenderWindow& gameWindow);
    void SetTexture(sf::RenderWindow& gameWindow, int textNum);
private:
    sf::Sprite happyFace;
    sf::Sprite debug;
    sf::Sprite leaderboard;
    const int num;
    int rowCount;
    int colCount;
};