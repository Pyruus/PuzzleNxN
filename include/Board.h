#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Tile.h"
#include "MoveDirection.h"

class Board {
private:
    int gridSize;
    std::vector<Tile*> tiles;

    bool isSolvable(const std::vector<int>& puzzle);
    int getInversionCount(const std::vector<int>& puzzle);

public:
    Board(int n);

    void initialize();

    void shuffle();
};

#endif // BOARD_H
