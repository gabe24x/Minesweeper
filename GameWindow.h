#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "TextureManager.h"
#include "Board.h"
#include "Button.h"
#include "Timer.h"
#include "LeaderboardWindow.h"
#pragma once

class GameWindow {
    int windowWidth;
    int windowHeight;
    int rowCount;
    int colCount;
    int mineCount;
    string userName;
public:
    GameWindow(int windowWidth, int windowHeight, int rowCount, int colCount, int mineCount, string& userName);
    void Display();
};
