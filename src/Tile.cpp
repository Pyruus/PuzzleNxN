#include "Tile.h"

Tile::Tile() : value(0), position({0, 0}) {}

Tile::Tile(int value, int x, int y) : value(value), position({x, y}) {}

int Tile::getValue() const {
    return value;
}

void Tile::setValue(int val) {
    value = val;
}

int Tile::getX() const {
    return position.x;
}

int Tile::getY() const {
    return position.y;
}

void Tile::setX(int x) {
    this->position.x = x;
}

void Tile::setY(int y) {
    this->position.y = y;
}

bool Tile::operator==(const Tile& other) const {
    return value == other.value;
}

bool Tile::operator!=(const Tile& other) const {
    return value != other.value;
}

bool Tile::operator<(const Tile& other) const {
    return value < other.value;
}
