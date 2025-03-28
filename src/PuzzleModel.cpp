#include "../include/PuzzleModel.h"

PuzzleModel::PuzzleModel(int size, QObject *parent) : QObject(parent), board(size){
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
        emit boardChanged(board);
        if (isSolved()) {
            emit gameSolved();
        }
    }
}

void PuzzleModel::shuffle() {
    board.shuffle();
    emit boardChanged(board);
}
