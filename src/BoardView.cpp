#include "BoardView.h"
#include <QGridLayout>

BoardView::BoardView(const Board &board, QWidget *parent) : QWidget(parent), size(board.getSize()) {
    QGridLayout *layout = new QGridLayout(this);
    layout->setSpacing(0);

    tileViews.resize(size, std::vector<TileView*>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            tileViews[i][j] = new TileView(board.getTile(i, j), board.getSize(), this);
            layout->addWidget(tileViews[i][j], i, j);
            connect(tileViews[i][j], &TileView::clicked, [this, i, j](){ emit tileClicked(i, j); });
        }
    }
    layout->setSpacing(5);
}

void BoardView::updateBoard(const Board &board) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            tileViews[i][j]->updateTile(board.getTile(i, j));
        }
    }
}
