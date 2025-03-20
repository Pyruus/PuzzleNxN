#include "../include/Tile.h"

Tile::Tile(int val) : value(val){}

int Tile::getValue() const {
    return value;
}

void Tile::setValue(int val) {
    value = val;
}

bool Tile::isEmpty() const {
    return value == 0;
}
