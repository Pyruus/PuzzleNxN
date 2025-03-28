#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "PuzzleModel.h"
#include "BoardView.h"
#include "ControlPanel.h"

#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

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
};
#endif // MAINWINDOW_H
