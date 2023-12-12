#include "Timer.h"

Timer::Timer(int r, int c) {
    rowCount = r;
    colCount = c;

    minutes0 = 0; //minutes index 0
    minutes1 = 0; // minutes index 1
    seconds0 = 0; // seconds index 0
    seconds1 = 0; // seconds index 1

    start_time = chrono::high_resolution_clock::now();

    pauseTime = chrono::high_resolution_clock::now();
    elapsed_paused_time = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - pauseTime).count();

    paused = false;

    sf::Texture& digitsText = TextureManager::getTexture("digits");
    digits.setTexture(digitsText);

    digitsMap = parseDigits(digits);

    sf::Texture& pauseText = TextureManager::getTexture("pause");
    pauseBttn.setTexture(pauseText);
    pauseBttn.setPosition(colCount * 32 - 240, 32 * (rowCount + 0.5));

    sf::Texture& playText = TextureManager::getTexture("play");
    playBttn.setTexture(playText);
    playBttn.setPosition(colCount * 32 - 240, 32 * (rowCount + 0.5));
}

map<int, sf::Sprite> Timer::parseDigits(sf::Sprite digitsSprite){
    map<int, sf::Sprite> digitsMap;

    for(int i = 0; i < 10; i++){
        sf::IntRect rect(i*21,0,21,32);
        digitsSprite.setTextureRect(rect);
        sf::Sprite sprite = digitsSprite;
        digitsMap.emplace(i, sprite);
    }

    return digitsMap;
}

void Timer::Draw(sf::RenderWindow& gameWindow) {
    //this finds the time elapsed, so the current time - the time the window opened.
    auto game_duration = std::chrono::duration_cast<std::chrono::seconds>(chrono::high_resolution_clock::now() - start_time);
    int total_time = game_duration.count(); // necessary to subtract elapsed time later because "game_duration.count()" is const

    int minutes;
    int seconds;

    if(!paused) {
        //enters if the game is NOT paused. This is the condition that keeps the timer from incrementing when paused.
        //cout << "not paused\n";
        total_time =  total_time - elapsed_paused_time; //
        minutes = total_time / 60;
        seconds = total_time % 60;
        //"separating" the integers. So.... 68 -> seconds0 = 6 and seconds1 = 8
        minutes0 = minutes / 10 % 10; //minutes index 0
        minutes1 = minutes % 10; // minutes index 1
        seconds0 = seconds / 10 % 10; // seconds index 0
        seconds1 = seconds % 10; // seconds index 1
    }

    digitsMap[minutes0].setPosition(colCount * 32 - 97, 32 * (rowCount + 0.5) + 16);
    gameWindow.draw(digitsMap[minutes0]);

    digitsMap[minutes1].setPosition(colCount * 32 - 76,  32 * (rowCount + 0.5) + 16);
    gameWindow.draw(digitsMap[minutes1]);

    digitsMap[seconds0].setPosition(colCount * 32 - 54,  32 * (rowCount + 0.5) + 16);
    gameWindow.draw(digitsMap[seconds0]);

    digitsMap[seconds1].setPosition(colCount * 32 - 33, 32 * (rowCount + 0.5) + 16);
    gameWindow.draw(digitsMap[seconds1]);

    gameWindow.draw(pauseBttn);

    if(paused){
        gameWindow.draw(playBttn);
    }

    gameWindow.display();

}

void Timer::PauseUnpause(sf::Event& event, sf::RenderWindow& gameWindow) {
    sf::Vector2i vec = sf::Mouse::getPosition(gameWindow);

    if (sf::Event::MouseButtonPressed == event.type && sf::Mouse::Left == event.mouseButton.button){
        if(pauseBttn.getGlobalBounds().contains(vec.x, vec.y)){
            paused = !paused; //boolean changed everytime pause button is clicked

            if(paused) {
                cout << "paused" << endl;
                pauseTime = chrono::high_resolution_clock::now();

            }else{
                //unpaused
                auto unPausedTime = chrono::high_resolution_clock::now();
                elapsed_paused_time += chrono::duration_cast<chrono::seconds>(unPausedTime - pauseTime).count(); //Addition is necessary for when hitting the pause button more than once
                //cout << elapsed_paused_time % 60 << " " << endl;
            }
        }
    }
}

bool Timer::IsPaused() {
    return paused;
}

void Timer::TogglePaused() {
    paused = !paused;
}

vector<int> Timer::GetWinningTime() {
    auto game_duration = std::chrono::duration_cast<std::chrono::seconds>(chrono::high_resolution_clock::now() - start_time);
    int total_time = game_duration.count(); // necessary to subtract elapsed time later because "game_duration.count()" is const

    int minutes;
    int seconds;

    total_time =  total_time - elapsed_paused_time; //
    minutes = total_time / 60;
    seconds = total_time % 60;
    vector<int> winningTime;
    winningTime.push_back(minutes);
    winningTime.push_back(seconds);
    return winningTime;
}
