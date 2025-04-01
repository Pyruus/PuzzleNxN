#include "../include/PuzzleModel.h"

PuzzleModel::PuzzleModel(int size, QObject *parent) : QObject(parent), board(size), moveCount(0){
    shuffle();
}

Board PuzzleModel::getBoard() const {
    return board;
}

bool PuzzleModel::isSolved() const {
    return board.isSolved();
}

bool PuzzleModel::isSolvable() const {
    return board.isSolvable();
}

void PuzzleModel::moveTile(MoveDirection direction) {
    if (board.moveTile(direction)) {
        moveCount++;
        emit boardChanged(board);
        emit moveCountChanged(moveCount);
        if (isSolved()) {
            emit gameSolved();
        }
    }
}

void PuzzleModel::shuffle() {
    board.shuffle();
    emit boardChanged(board);
    emit moveCountChanged(moveCount);
}

int PuzzleModel::getMoveCount() const {
    return moveCount;
}
