#include "../include/Heuristic.h"
#include <cmath>

int ManhattanDistance::calculate(const Board &board) const {
    int distance = 0;
    int size = board.getSize();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Tile tile = board.getTile(i, j);
            if (tile.getValue() != 0) {
                int targetX = (tile.getValue() - 1) / size;
                int targetY = (tile.getValue() - 1) % size;
                distance += std::abs(i - targetX) + std::abs(j - targetY);
            }
        }
    }
    return distance;
}

int MisplacedTiles::calculate(const Board &board) const {
    int misplaced = 0;
    int size = board.getSize();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board.getTile(i, j).getValue() != (i * size + j + 1) && board.getTile(i, j).getValue() != 0) {
                misplaced++;
            }
        }
    }
    return misplaced;
}
