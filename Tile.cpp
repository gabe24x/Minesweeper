#include "Tile.h"

Tile::Tile() {
    sf::Texture& tileTexture = TextureManager::getTexture("tile_hidden");
    tileSprite.setTexture(tileTexture);
    tileSprite.setPosition(x_pos, y_pos);
    tileSprite.setOrigin(static_cast<float>(tileTexture.getSize().x) / 2.0f, static_cast<float>(tileTexture.getSize().y) / 2.0f);
    hasMine = false;
    revealed = false;
    flagged = false;

    auto iter = adjacentTiles.begin();
    for (; iter != adjacentTiles.end(); ++iter) {
        if ((*iter)->GetHasMine())
            ++adjacentMines;
    }
}

void Tile::SetHasMine(bool val) {
    this->hasMine = val;
}

bool Tile::GetHasMine() {
    return hasMine;
}

void Tile::Reveal() {
    revealed = true;
}

bool Tile::IsRevealed() const {
    return revealed;
}

void Tile::ToggleFlag() {
    flagged = !flagged;
}

void Tile::SetSprite(std::string texture) {
    sf::Texture newTexture = TextureManager::getTexture(texture);
    tileSprite.setTexture(newTexture);
}

sf::Sprite Tile::GetSprite() {
    return tileSprite;
}

void Tile::SetPosition(float x, float y) {
    x_pos = x;
    y_pos = y;
}

bool Tile::IsFlagged() {
    return flagged;
}

void Tile::AddAdjacentTile(Tile* adjacent) {
    adjacentTiles.push_back(adjacent);
}

const std::vector<Tile*>& Tile::GetAdjacentTiles() const {
    return adjacentTiles;
}

int Tile::GetAdjacentMines() const {
    int count = 0;
    for (Tile* adjacent : adjacentTiles)
        if (adjacent->GetHasMine())
            ++count;
    return count;
}

float Tile::GetX() {
    return x_pos;
}

float Tile::GetY() {
    return y_pos;
}