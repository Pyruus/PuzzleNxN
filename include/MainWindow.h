#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Board.h"

#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int size = 4, QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void createPuzzle();

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *buttonLayout;
    QLabel *moveCountLabel;
    QPushButton *newGameButton;
    QComboBox *sizeComboBox;

    Board* board;
};
#endif // MAINWINDOW_H
