#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Textbox.h"
#pragma once

class LeaderboardWindow {
    int windowWidth;
    int windowHeight;
    bool displayed;
public:
    struct LeaderboardEntry {
        std::string time;
        std::string name;
    };
    LeaderboardWindow(int windowWidth, int windowHeight);
    void Display();
    bool IsDisplayed();
    void ToggleDisplayed();
    //void SetWinningTime(vector<int> winningTime, std::string& userName);
};
