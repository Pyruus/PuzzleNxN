#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "PuzzleModel.h"
#include "BoardView.h"
#include "ControlPanel.h"
#include "StatisticsView.h"

#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int size, QWidget *parent = nullptr);

private:
    PuzzleModel puzzleModel;
    BoardView *boardView;
    ControlPanel *controlPanel;
    QComboBox *boardSizeComboBox;
    StatisticsView *statisticsView;
    QTimer *timer;
    int elapsedTime = 0;
    bool gameFinished = false;

private slots:
    void updateTime();
    void saveGame();
    void loadGame();
};
#endif // MAINWINDOW_H
