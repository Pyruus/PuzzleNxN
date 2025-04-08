#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "Board.h"

class Heuristic {
public:
    virtual int calculate(const Board &board) const = 0;
    virtual ~Heuristic() {}
};

class ManhattanDistance : public Heuristic {
public:
    int calculate(const Board &board) const override;
};

class MisplacedTiles : public Heuristic {
public:
    int calculate(const Board &board) const override;
};

#endif // HEURISTIC_H
