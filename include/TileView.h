#ifndef TILEVIEW_H
#define TILEVIEW_H

#include <QWidget>
#include <QLabel>
#include "tile.h"

    class TileView : public QWidget {
    Q_OBJECT

public:
    TileView(const Tile &tile, QWidget *parent = nullptr);
    void updateTile(const Tile &tile);
    void mousePressEvent(QMouseEvent *event);

signals:
    void clicked();

private:
    QLabel *label;
    void setOpacity(qreal opacity);
};

#endif // TILEVIEW_H
