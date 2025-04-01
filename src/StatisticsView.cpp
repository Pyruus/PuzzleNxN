#include "../include/StatisticsView.h"
#include <QGridLayout>

StatisticsView::StatisticsView(QWidget *parent) : QWidget(parent) {
    QGridLayout *layout = new QGridLayout(this);
    moveCountLabel = new QLabel("Moves: 0", this);
    messageLabel = new QLabel("", this);

    layout->addWidget(moveCountLabel, 0, 0);
    layout->addWidget(messageLabel, 1, 0);
}

void StatisticsView::updateMoveCount(int moveCount) {
    moveCountLabel->setText("Moves: " + QString::number(moveCount));
}

void StatisticsView::displayMessage(const QString &message) {
    messageLabel->setText(message);
}
