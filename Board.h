#include "Tile.h"
#include <vector>
#include <random>
#pragma once

class Board {
    vector<Tile> tiles;
    int rowCount;
    int colCount;
    int mineCount;
    static std::default_random_engine generator;
public:
    Board(int rowCount, int colCount, int mineCount);
    void Draw(sf::RenderWindow& gameWindow);
    void Click(sf::Event& event, sf::RenderWindow& gameWindow);
    void SetupAdjacentTiles();
    void RecursiveReveal(int row, int col);
    void ToggleShowMines(sf::RenderWindow& gameWindow);
    bool CheckLoss();
    bool CheckWin();
};