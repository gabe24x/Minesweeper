#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "WelcomeWindow.h"
#include "GameWindow.h"
#include "LeaderboardWindow.h"

int main() {
    std::ifstream file("config.cfg");

    std::string line1, line2, line3;

    if (file.is_open()) {
        std::getline(file, line1);
        std::getline(file, line2);
        std::getline(file, line3);
    }
    else {
        std::cerr << "Unable to open config file." << std::endl;
    }

    file.close();

    int colCount = stoi(line1);
    int rowCount = stoi(line2);
    int mineCount = stoi(line3);

    int windowWidth = colCount * 32;
    int windowHeight = rowCount * 32 + 100;

    WelcomeWindow welcomeWindow = WelcomeWindow(windowWidth, windowHeight);
    std::string userName = welcomeWindow.Display();

    GameWindow gameWindow = GameWindow(windowWidth, windowHeight, rowCount, colCount, mineCount, userName);
    gameWindow.Display();

    return 0;
}