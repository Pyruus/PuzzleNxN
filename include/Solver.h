#ifndef SOLVER_H
#define SOLVER_H

#include "Board.h"
#include "MoveDirection.h"
#include "Heuristic.h"
#include <vector>

class Solver {
public:
    virtual std::vector<MoveDirection> solve(const Board &board) = 0;
    virtual ~Solver() {}
};

class AStarSolver : public Solver {
public:
    std::vector<MoveDirection> solve(const Board &board) override;
};

namespace {
struct IDAStarNode {
    Board board;
    int g;
    std::vector<MoveDirection> path;
};
}

class IDAStarSolver : public Solver {
public:
    std::vector<MoveDirection> solve(const Board &board) override;
private:
    int search(IDAStarNode node, int bound, const ManhattanDistance &heuristic, std::vector<MoveDirection> &solution);
};

#endif // SOLVER_H
