#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "PuzzleModel.h"
#include "BoardView.h"
#include "ControlPanel.h"
#include "StatisticsView.h"
#include "Solver.h"

#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QMessageBox>

class AlgorithmWorker : public QObject {
    Q_OBJECT
public:
    AlgorithmWorker(Board initialBoard);

signals:
    void finished(std::vector<MoveDirection> aStarMoves, std::vector<MoveDirection> idaStarMoves);

public slots:
    void runAStar();
    void runIDAStar();

private:
    Board initialBoard;
    AStarSolver aStarSolver;
    IDAStarSolver idaStarSolver;
    std::vector<MoveDirection> aStarResult;
    std::vector<MoveDirection> idaStarResult;
};

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
    QDialog *solutionsDialog = nullptr;

private slots:
    void updateTime();
    void displaySolutions(std::vector<MoveDirection> aStarMoves, std::vector<MoveDirection> idaStarMoves);
};
#endif // MAINWINDOW_H
