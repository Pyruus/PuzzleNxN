#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QWidget>
#include <vector>
#include "board.h"
#include "tileview.h"

class BoardView : public QWidget {
    Q_OBJECT

public:
    BoardView(const Board &board, QWidget *parent = nullptr);
    void updateBoard(const Board &board);

signals:
    void tileClicked(int x, int y);

private:
    std::vector<std::vector<TileView*>> tileViews;
    int size;
};

#endif // BOARDVIEW_H
