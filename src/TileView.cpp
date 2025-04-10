#include "TileView.h"
#include <QGraphicsOpacityEffect>
#include <QGridLayout>

TileView::TileView(const Tile &tile, QWidget *parent, int boardSize) : QWidget(parent) {
    QGridLayout *layout = new QGridLayout(this);
    label = new QLabel(QString::number(tile.getValue()), this);
    label->setAlignment(Qt::AlignCenter);
    QFont font("Arial", 24 * 8. / boardSize, QFont::Bold);
    label->setFont(font);
    layout->addWidget(label, 0, 0);
    setStyleSheet("border: 2px solid black; background-color: lightgreen;");
    setFixedSize(100. * 8. / boardSize, 100. * 8. / boardSize);
    if (tile.getValue() == 0) {
        setOpacity(0);
    } else {
        setOpacity(1);
    }
}

void TileView::updateTile(const Tile &tile) {
    label->setText(QString::number(tile.getValue()));
    if (tile.getValue() == 0) {
        setOpacity(0);
    } else {
        setOpacity(1);
    }
}

void TileView::mousePressEvent(QMouseEvent *event) {
    emit clicked();
}

void TileView::setOpacity(qreal opacity) {
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(opacity);
    setGraphicsEffect(effect);
}
