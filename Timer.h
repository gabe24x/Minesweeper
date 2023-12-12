#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
using namespace std;

class Timer {
public:
    Timer(int r, int c);
    map<int, sf::Sprite> parseDigits(sf::Sprite digitsSprite);
    void Draw(sf::RenderWindow& gameWindow);
    void PauseUnpause(sf::Event& event, sf::RenderWindow& gameWindow);
    bool IsPaused();
    void TogglePaused();
    vector<int> GetWinningTime();
private:
    int minutes0; //minutes index 0
    int minutes1; // minutes index 1
    int seconds0; // seconds index 0
    int seconds1; // seconds index 1
    int rowCount;
    int colCount;
    sf::Sprite digits;
    sf::Sprite pauseBttn;
    sf::Sprite playBttn;
    map<int, sf::Sprite> digitsMap;
    bool paused;
    std::chrono::time_point<std::chrono::high_resolution_clock> pauseTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::duration<long long int>::rep elapsed_paused_time;
};