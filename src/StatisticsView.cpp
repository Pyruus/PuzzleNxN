#include "../include/StatisticsView.h"
#include <QGridLayout>

StatisticsView::StatisticsView(QWidget *parent) : QWidget(parent) {
    QGridLayout *layout = new QGridLayout(this);
    moveCountLabel = new QLabel("Moves: 0", this);
    timeLabel = new QLabel("Time: 00:00:00", this);

    layout->addWidget(moveCountLabel, 0, 0);
    layout->addWidget(timeLabel, 1, 0);

}

void StatisticsView::updateMoveCount(int moveCount) {
    moveCountLabel->setText("Moves: " + QString::number(moveCount));
}


void StatisticsView::updateTime(int hours, int minutes, int seconds) {
    QString timeString = QString("Time: %1:%2:%3").arg(hours, 2, 10, QLatin1Char('0')).arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));
    timeLabel->setText(timeString);
}
