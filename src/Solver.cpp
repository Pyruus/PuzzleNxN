#include "../include/Solver.h"
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <limits>

struct Node {
    Board board;
    int g;
    int h;
    std::vector<MoveDirection> path;

    bool operator>(const Node &other) const {
        return (g + h) > (other.g + other.h);
    }
};

std::vector<MoveDirection> AStarSolver::solve(const Board &initialBoard) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    std::map<Board, int> closedSet;
    ManhattanDistance heuristic;

    Node startNode = {initialBoard, 0, heuristic.calculate(initialBoard), {}};
    openSet.push(startNode);
    closedSet[initialBoard] = 0;

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.board.isSolved()) {
            return current.path;
        }

        if (closedSet.count(current.board) && current.g > closedSet[current.board]) {
            continue;
        }

        for (MoveDirection direction : {MoveDirection::UP, MoveDirection::DOWN, MoveDirection::LEFT, MoveDirection::RIGHT}) {
            Board nextBoard = current.board;
            if (nextBoard.moveTile(direction)) {
                int newG = current.g + 1;
                int newH = heuristic.calculate(nextBoard);

                if (!closedSet.count(nextBoard) || newG < closedSet[nextBoard]) {
                    Node nextNode = {nextBoard, newG, newH, current.path};
                    nextNode.path.push_back(direction);
                    openSet.push(nextNode);
                    closedSet[nextBoard] = newG;
                }
            }
        }
    }
    return {};
}

int IDAStarSolver::search(IDAStarNode node, int bound, const ManhattanDistance &heuristic, std::vector<MoveDirection> &solution) {
    int f = node.g + heuristic.calculate(node.board);
    if (f > bound) {
        return f;
    }
    if (node.board.isSolved()) {
        solution = node.path;
        return -1;
    }
    int min = std::numeric_limits<int>::max();
    for (MoveDirection direction : {MoveDirection::UP, MoveDirection::DOWN, MoveDirection::LEFT, MoveDirection::RIGHT}) {
        Board nextBoard = node.board;
        if (nextBoard.moveTile(direction)) {
            IDAStarNode nextNode = {nextBoard, node.g + 1, node.path};
            nextNode.path.push_back(direction);
            int t = search(nextNode, bound, heuristic, solution);
            if (t == -1) {
                return -1;
            }
            if (t < min) {
                min = t;
            }
        }
    }
    return min;
}

std::vector<MoveDirection> IDAStarSolver::solve(const Board &initialBoard) {
    ManhattanDistance heuristic;
    IDAStarNode startNode = {initialBoard, 0, {}};
    int bound = heuristic.calculate(initialBoard);
    std::vector<MoveDirection> solution;
    while (true) {
        int t = search(startNode, bound, heuristic, solution);
        if (t == -1) {
            return solution;
        }
        if (t == std::numeric_limits<int>::max()) {
            return {};
        }
        bound = t;
    }
}
