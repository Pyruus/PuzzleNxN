#include "../include/Tile.h"

Tile::Tile() : value(0), x(0), y(0) {}

Tile::Tile(int value, int x, int y) : value(value), x(x), y(y) {}

int Tile::getValue() const {
    return value;
}

void Tile::setValue(int val) {
    value = val;
}

int Tile::getX() const {
    return x;
}

int Tile::getY() const {
    return y;
}

void Tile::setX(int x) {
    this->x = x;
}

void Tile::setY(int y) {
    this->y = y;
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
