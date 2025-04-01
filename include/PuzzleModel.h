#ifndef PUZZLEMODEL_H
#define PUZZLEMODEL_H

#include "Board.h"
#include "MoveDirection.h"
#include <QObject>

class PuzzleModel : public QObject {
    Q_OBJECT

public:
    PuzzleModel(int size, QObject *parent = nullptr);
    Board getBoard() const;
    bool isSolved() const;
    bool isSolvable() const;
    int getMoveCount() const;

public slots:
    void moveTile(MoveDirection direction);
    void shuffle();

signals:
    void boardChanged(const Board &board);
    void moveCountChanged(int moveCount);
    void gameSolved();

private:
    Board board;
    int moveCount;
};

#endif // PUZZLEMODEL_H
