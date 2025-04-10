#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "MoveDirection.h"
#include "Tile.h"

class Board {
private:
    int size;
    std::vector<std::vector<Tile>> tiles;

public:
    Board(int size);
    Tile getTile(int x, int y) const;
    bool moveTile(MoveDirection direction);
    void shuffle();
    int getSize() const;
    bool isSolved() const;
    bool isSolvable() const;
    bool operator<(const Board& other) const;
    std::vector<std::vector<Tile>> getTiles() const;
    void setTileValue(int row, int col, int value);
};

#endif // BOARD_H
