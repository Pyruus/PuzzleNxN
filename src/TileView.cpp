#include "../include/TileView.h"
#include <QGridLayout>

TileView::TileView(const Tile &tile, QWidget *parent) : QWidget(parent) {
    QGridLayout *layout = new QGridLayout(this);
    label = new QLabel(QString::number(tile.getValue()), this);
    label->setAlignment(Qt::AlignCenter);
    QFont font("Arial", 24, QFont::Bold);
    label->setFont(font);
    layout->addWidget(label, 0, 0);
    setStyleSheet("border: 2px solid black; background-color: lightgreen;");
    setFixedSize(80, 80);
}

void TileView::updateTile(const Tile &tile) {
    label->setText(QString::number(tile.getValue()));
}

void TileView::mousePressEvent(QMouseEvent *event) {
    emit clicked();
}
