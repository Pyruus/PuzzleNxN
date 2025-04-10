#include "Board.h"
#include <iostream>
#include <algorithm>
#include <random>

Board::Board(int size) : size(size) {
    tiles.resize(size, std::vector<Tile>(size));
    int value = 1;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (value < size * size) {
                tiles[i][j] = Tile(value++, i, j);
            } else {
                tiles[i][j] = Tile(0, i, j);
            }
        }
    }
}

Tile Board::getTile(int x, int y) const {
    return tiles[x][y];
}

bool Board::moveTile(MoveDirection direction) {
    int emptyX = -1, emptyY = -1;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (tiles[i][j].getValue() == 0) {
                emptyX = i;
                emptyY = j;
                break;
            }
        }
    }

    int newX = emptyX, newY = emptyY;
    switch (direction) {
    case MoveDirection::UP: newX++; break;
    case MoveDirection::DOWN: newX--; break;
    case MoveDirection::LEFT: newY++; break;
    case MoveDirection::RIGHT: newY--; break;
    }

    if (newX >= 0 && newX < size && newY >= 0 && newY < size) {
        std::swap(tiles[emptyX][emptyY], tiles[newX][newY]);
        tiles[emptyX][emptyY].setX(emptyX);
        tiles[emptyX][emptyY].setY(emptyY);
        tiles[newX][newY].setX(newX);
        tiles[newX][newY].setY(newY);
        return true;
    }
    return false;
}

void Board::shuffle() {
    do{
        std::vector<int> values(size * size);
        for (int i = 0; i < size * size - 1; ++i) {
            values[i] = i + 1;
        }
        values[size * size - 1] = 0;

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(values.begin(), values.end(), g);

        int k = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                tiles[i][j] = Tile(values[k++], i, j);
            }
        }
    }while (!isSolvable());
}

int Board::getSize() const {
    return size;
}

bool Board::isSolved() const {
    int value = 1;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (tiles[i][j].getValue() != value && value < size * size) {
                return false;
            }
            value++;
        }
    }
    return true;
}

bool Board::isSolvable() const {
    std::vector<int> flattenedBoard;
    int inversions = 0;
    int blank_row = -1;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            flattenedBoard.push_back(tiles[i][j].getValue());
            if (tiles[i][j].getValue() == 0){
                blank_row = i;
            }
        }
    }

    for (int i = 0; i < size * size; ++i) {
        if (flattenedBoard[i] == 0){
            continue;
        }
        for (int j = i + 1; j < size * size; ++j) {
            if (flattenedBoard[j] != 0 && flattenedBoard[i] > flattenedBoard[j]) {
                inversions++;
            }
        }
    }

    if (size % 2 == 1) {
        return (inversions % 2 == 0);
    } else {
        int blankRowFromBottom = size - 1 - blank_row;
        return ((inversions % 2 == 0) && (blankRowFromBottom % 2 == 0)) ||
               ((inversions % 2 != 0) && (blankRowFromBottom % 2 != 0));
    }
}

bool Board::operator<(const Board& other) const {
    if (size != other.size) {
        return size < other.size;
    }
    return tiles < other.tiles;
std::vector<std::vector<Tile>> Board::getTiles() const{
    return tiles;
}

void Board::setTileValue(int row, int col, int value) {
    if (row >= 0 && row < size && col >= 0 && col < size) {
        tiles[row][col].setValue(value);
    }
}
