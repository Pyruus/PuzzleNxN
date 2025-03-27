#include "../include/Board.h"
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
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            flattenedBoard.push_back(tiles[i][j].getValue());
        }
    }

    int inversions = 0;
    for (size_t i = 0; i < flattenedBoard.size(); ++i) {
        for (size_t j = i + 1; j < flattenedBoard.size(); ++j) {
            if (flattenedBoard[i] != 0 && flattenedBoard[j] != 0 && flattenedBoard[i] > flattenedBoard[j]) {
                inversions++;
            }
        }
    }

    if (size % 2 == 1) {
        return inversions % 2 == 0;
    } else {
        int emptyRow = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (tiles[i][j].getValue() == 0) {
                    emptyRow = size - i;
                    break;
                }
            }
        }
        return (inversions + emptyRow) % 2 == 0;
    }
}
