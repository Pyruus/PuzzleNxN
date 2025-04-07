#ifndef STATISTICSVIEW_H
#define STATISTICSVIEW_H

#include <QWidget>
#include <QLabel>

class StatisticsView : public QWidget {
    Q_OBJECT

public:
    StatisticsView(QWidget *parent = nullptr);
    void updateMoveCount(int moveCount);
    void updateTime(int hours, int minutes, int seconds);

private:
    QLabel *moveCountLabel;
    QLabel *timeLabel;
};


#endif // STATISTICSVIEW_H
