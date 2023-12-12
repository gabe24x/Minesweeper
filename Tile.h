#include <SFML/Graphics.hpp>
#include <vector>
#include "TextureManager.h"
#pragma once

class Tile {
public:
    Tile();
    void Reveal();
    void SetHasMine(bool val);
    bool GetHasMine();
    void SetSprite(std::string texture);
    sf::Sprite GetSprite();
    void SetPosition(float x, float y);
    bool IsRevealed() const;
    void ToggleFlag();
    bool IsFlagged();
    void AddAdjacentTile(Tile* adjacent);
    const std::vector<Tile*>& GetAdjacentTiles() const;
    int GetAdjacentMines() const;
    float GetX();
    float GetY();
private:
    sf::Sprite tileSprite;
    float x_pos;
    float y_pos;
    bool revealed;
    bool hasMine;
    bool flagged;
    std::vector<Tile*> adjacentTiles;
    int adjacentMines;
};