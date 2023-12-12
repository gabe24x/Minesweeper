#include "Button.h"

Button::Button(int num, int rowCount, int colCount) : num(num) {
    this->rowCount = rowCount;
    this->colCount = colCount;

    if (num == 1) {
        sf::Texture& happyFaceTexture = TextureManager::getTexture("face_happy");
        happyFace.setTexture(happyFaceTexture);
        happyFace.setPosition(colCount / 2.0 * 32 - 32, 32 * (rowCount + 0.5));
    }
    if (num == 3) {
        sf::Texture &debugTexture = TextureManager::getTexture("debug");
        debug.setTexture(debugTexture);
        debug.setPosition(colCount * 32 - 304, 32 * (rowCount + 0.5));
    }
    if (num == 4) {
        sf::Texture &leaderboardTexture = TextureManager::getTexture("leaderboard");
        leaderboard.setTexture(leaderboardTexture);
        leaderboard.setPosition(colCount * 32 - 176, 32 * (rowCount + 0.5));
    }
}

void Button::Draw(sf::RenderWindow& gameWindow) {
    if (num == 1)
        gameWindow.draw(happyFace);
    else if (num == 3)
        gameWindow.draw(debug);
    else if (num == 4)
        gameWindow.draw(leaderboard);
}

bool Button::Click(sf::Event& event, sf::RenderWindow& gameWindow) {
    sf::Vector2i mouse = sf::Mouse::getPosition(gameWindow);

    if (num == 1 && happyFace.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
        return true;
    }

    else if (num == 3 && debug.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
        return true;
    }

    else if (num == 4 && leaderboard.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
        return true;
    }
    return false;
}

void Button::SetTexture(sf::RenderWindow &gameWindow, int textNum) {
    if (num == 1) {
        if (textNum == 1) {
            sf::Texture& winFaceTexture = TextureManager::getTexture("face_win");
            happyFace.setTexture(winFaceTexture);
            gameWindow.draw(happyFace);
        }
        else if (textNum == 2) {
            sf::Texture& loseFaceTexture = TextureManager::getTexture("face_lose");
            happyFace.setTexture(loseFaceTexture);
        }
        else if (textNum == 3) {
            sf::Texture& happyFaceTexture = TextureManager::getTexture("face_happy");
            happyFace.setTexture(happyFaceTexture);
        }
    }
}