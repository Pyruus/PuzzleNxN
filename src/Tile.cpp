#include "../include/Tile.h"

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
