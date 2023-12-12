#include "Board.h"
#include <iostream>

std::default_random_engine Board::generator;

Board::Board(int rowCount, int colCount, int mineCount) {
    this->rowCount = rowCount;
    this->colCount = colCount;
    this->mineCount = mineCount;
    std::vector<int> mineTiles;
    int numMineTiles = 0;

    std::uniform_int_distribution<int> distribution(0, rowCount * colCount - 1);

    while (numMineTiles < mineCount) {
        int randomNumber = distribution(generator);

        if (std::find(mineTiles.begin(), mineTiles.end(), randomNumber) == mineTiles.end()) {
            mineTiles.push_back(randomNumber);
            ++numMineTiles;
        }
    }

    for (int i = 0; i < rowCount * colCount; ++i) {
        Tile tile;
        tiles.push_back(tile);

        if (std::find(mineTiles.begin(), mineTiles.end(), i) != mineTiles.end()) {
            tiles[i].SetHasMine(true);
        }
    }

    SetupAdjacentTiles();
}

void Board::Draw(sf::RenderWindow& gameWindow) {
    sf::Texture& hiddenTexture = TextureManager::getTexture("tile_hidden");
    sf::Texture& mineTexture = TextureManager::getTexture("mine");
    sf::Texture& revealedTexture = TextureManager::getTexture("tile_revealed");
    sf::Texture& flagTexture = TextureManager::getTexture("flag");
    sf::Texture& oneTexture = TextureManager::getTexture("number_1");
    sf::Texture& twoTexture = TextureManager::getTexture("number_2");
    sf::Texture& threeTexture = TextureManager::getTexture("number_3");
    sf::Texture& fourTexture = TextureManager::getTexture("number_4");
    sf::Texture& fiveTexture = TextureManager::getTexture("number_5");
    sf::Texture& sixTexture = TextureManager::getTexture("number_6");
    sf::Texture& sevenTexture = TextureManager::getTexture("number_7");
    sf::Texture& eightTexture = TextureManager::getTexture("number_8");

    const float tileSize = hiddenTexture.getSize().x;

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            int index = row * colCount + col;
            Tile& tile = tiles[index];

            sf::Sprite tileSprite;

            if (tile.GetHasMine() && tile.IsRevealed()) {
                tileSprite.setTexture(mineTexture);
            } else if (tile.IsRevealed()) {
                tileSprite.setTexture(tile.GetHasMine() ? hiddenTexture : revealedTexture);
            } else {
                tileSprite.setTexture(hiddenTexture);
            }

            tileSprite.setOrigin(tileSize / 2.0f, tileSize / 2.0f);

            float x = col * tileSize + (tileSize / 2.0f);
            float y = row * tileSize + (tileSize / 2.0f);

            tileSprite.setPosition(x, y);

            gameWindow.draw(tileSprite);

            if (tile.IsRevealed() && !tile.GetHasMine()) {
                sf::Sprite numSprite;
                numSprite.setTexture(revealedTexture);
                numSprite.setOrigin(tileSize / 2.0f, tileSize / 2.0f);
                numSprite.setPosition(x, y);

                if (tile.GetAdjacentMines() == 1)
                    numSprite.setTexture(oneTexture);
                else if (tile.GetAdjacentMines() == 2)
                    numSprite.setTexture(twoTexture);
                else if (tile.GetAdjacentMines() == 3)
                    numSprite.setTexture(threeTexture);
                else if (tile.GetAdjacentMines() == 4)
                    numSprite.setTexture(fourTexture);
                else if (tile.GetAdjacentMines() == 5)
                    numSprite.setTexture(fiveTexture);
                else if (tile.GetAdjacentMines() == 6)
                    numSprite.setTexture(sixTexture);
                else if (tile.GetAdjacentMines() == 7)
                    numSprite.setTexture(sevenTexture);
                else if (tile.GetAdjacentMines() == 8)
                    numSprite.setTexture(eightTexture);

                gameWindow.draw(numSprite);
            }

            if (tile.IsFlagged()) {
                sf::Sprite flagSprite;
                flagSprite.setTexture(flagTexture);
                flagSprite.setOrigin(tileSize / 2.0f, tileSize / 2.0f);
                flagSprite.setPosition(x, y);
                gameWindow.draw(flagSprite);
            }
        }
    }
}

void Board::RecursiveReveal(int row, int col) {
    // Check if the coordinates are within the board bounds
    if (row < 0 || row >= rowCount || col < 0 || col >= colCount) {
        return;
    }

    int index = row * colCount + col;
    Tile &tile = tiles[index];

    // Base case: stop recursion if the tile is already revealed or has a mine
    if (tile.IsRevealed()) {
        return;
    } else if (tile.GetHasMine()) {
        tile.Reveal();
        return;
    }

    // Reveal the current tile
    tile.Reveal();

    // If the current tile has no adjacent mines, recursively reveal adjacent tiles
    if (tile.GetAdjacentMines() == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                // Avoid revisiting the current tile
                if (i == 0 && j == 0) {
                    continue;
                }

                int newRow = row + i;
                int newCol = col + j;

                // Recursively reveal adjacent tiles
                RecursiveReveal(newRow, newCol);
            }
        }
    }
}





void Board::Click(sf::Event& event, sf::RenderWindow& gameWindow) {
    sf::Vector2i mouse = sf::Mouse::getPosition(gameWindow);

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            int index = row * colCount + col;
            Tile &tile = tiles[index];

            float tileSize = TextureManager::getTexture("tile_hidden").getSize().x;
            float y = row * tileSize + (tileSize / 2.0f);
            float x = col * tileSize + (tileSize / 2.0f);

            if (event.mouseButton.button == sf::Mouse::Left) {
                if (mouse.x >= x - tileSize / 2.0f && mouse.x < x + tileSize / 2.0f &&
                    mouse.y >= y - tileSize / 2.0f && mouse.y < y + tileSize / 2.0f) {
                    std::cout << "Tile clicked at Row: " << row << "\t";
                    std::cout << "Column: " << col << "\t";
                    std::cout << "Adjacent mines: " << tile.GetAdjacentMines() << std::endl;

                    // If the clicked tile has no adjacent mines, recursively reveal adjacent tiles
                    if (tile.IsFlagged())
                        continue;
                    else if (tile.GetAdjacentMines() == 0) {
                        RecursiveReveal(row, col);
                    } else {
                        tile.Reveal();
                    }
                }
            }

            else if (event.mouseButton.button == sf::Mouse::Right) {
                if (mouse.x >= x - tileSize / 2.0f && mouse.x < x + tileSize / 2.0f &&
                    mouse.y >= y - tileSize / 2.0f && mouse.y < y + tileSize / 2.0f) {
                    tile.ToggleFlag();
                }
            }
        }
    }
}

void Board::SetupAdjacentTiles() {
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            int index = row * colCount + col;
            Tile& tile = tiles[index];

            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (i == 0 && j == 0) {
                        continue;
                    }

                    int newRow = row + i;
                    int newCol = col + j;

                    if (newRow >= 0 && newRow < rowCount && newCol >= 0 && newCol < colCount) {
                        int newIndex = newRow * colCount + newCol;
                        Tile& adjacentTile = tiles[newIndex];

                        tile.AddAdjacentTile(&adjacentTile);
                    }
                }
            }
        }
    }
}

void Board::ToggleShowMines(sf::RenderWindow& gameWindow) {
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            int index = row * colCount + col;
            Tile &tile = tiles[index];

            float tileSize = TextureManager::getTexture("tile_hidden").getSize().x;
            float y = row * tileSize + (tileSize / 2.0f);
            float x = col * tileSize + (tileSize / 2.0f);

            if (tile.GetHasMine()) {
                sf::Texture mineTexture = TextureManager::getTexture("mine");
                sf::Sprite mineSprite;
                mineSprite.setOrigin(tileSize / 2.0f, tileSize / 2.0f);
                mineSprite.setTexture(mineTexture);
                mineSprite.setPosition(x, y);
                gameWindow.draw(mineSprite);
            }
        }
    }
}

bool Board::CheckLoss() {
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col)
        {
            int index = row * colCount + col;
            Tile &tile = tiles[index];
            if (tile.IsRevealed() && tile.GetHasMine())
                return true;
        }
    }
    return false;
}

bool Board::CheckWin() {
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            int index = row * colCount + col;
            Tile &tile = tiles[index];
            if (!tile.IsRevealed() && !tile.GetHasMine()) {
                return false;
            }
        }
    }
    return true;
}