#include "../include/MainWindow.h"

#include <QThread>

AlgorithmWorker::AlgorithmWorker(Board initialBoard) : initialBoard(initialBoard) {}

void AlgorithmWorker::runAStar() {
    aStarResult = aStarSolver.solve(initialBoard);
    emit finished(aStarResult, idaStarResult);
}

void AlgorithmWorker::runIDAStar() {
    idaStarResult = idaStarSolver.solve(initialBoard);
    emit finished(aStarResult, idaStarResult);
}

MainWindow::MainWindow(int size, QWidget *parent) : QMainWindow(parent), puzzleModel(size) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QGridLayout *layout = new QGridLayout(centralWidget);

    boardView = new BoardView(puzzleModel.getBoard(), this);
    controlPanel = new ControlPanel(this);
    statisticsView = new StatisticsView(this);

    QPushButton *newGameButton = new QPushButton("New Game", this);
    QLabel *boardSizeLabel = new QLabel("Board size", this);
    boardSizeComboBox = new QComboBox(this);
    boardSizeComboBox->addItem("3x3");
    boardSizeComboBox->addItem("4x4");
    boardSizeComboBox->addItem("5x5");
    boardSizeComboBox->setCurrentText(QString::number(size) + "x" + QString::number(size));

    layout->addWidget(boardView, 0, 0, 1, 1);
    layout->addWidget(newGameButton, 0, 1, 1, 1);
    layout->addWidget(boardSizeLabel, 1, 1, 1, 1);
    layout->addWidget(boardSizeComboBox, 2, 1, 1, 1);
    layout->addWidget(statisticsView, 3, 1, 1, 1);

    connect(newGameButton, &QPushButton::clicked, [this, layout](){
        this->gameFinished = false;

        int newSize = boardSizeComboBox->currentText().left(1).toInt();

        puzzleModel.~PuzzleModel();

        new (&puzzleModel) PuzzleModel(newSize, this);

        puzzleModel.shuffle();
        statisticsView->updateMoveCount(0);

        delete boardView;
        boardView = new BoardView(puzzleModel.getBoard(), this);
        layout->addWidget(boardView, 0, 0, 1, 1);

        connect(boardView, &BoardView::tileClicked, [this](int x, int y) {
            if (gameFinished) {
                return;
            }
            Board board = puzzleModel.getBoard();
            int emptyX = -1, emptyY = -1;
            for (int i = 0; i < board.getSize(); ++i) {
                for (int j = 0; j < board.getSize(); ++j) {
                    if (board.getTile(i, j).getValue() == 0) {
                        emptyX = i;
                        emptyY = j;
                        break;
                    }
                }
            }

            if ((abs(x - emptyX) == 1 && y == emptyY) || (x == emptyX && abs(y - emptyY) == 1)) {
                if (x > emptyX) { puzzleModel.moveTile(MoveDirection::UP); }
                else if (x < emptyX) { puzzleModel.moveTile(MoveDirection::DOWN); }
                else if (y > emptyY) { puzzleModel.moveTile(MoveDirection::LEFT); }
                else if (y < emptyY) { puzzleModel.moveTile(MoveDirection::RIGHT); }
            }
        });

        connect(&puzzleModel, &PuzzleModel::boardChanged, boardView, &BoardView::updateBoard);
        connect(&puzzleModel, &PuzzleModel::moveCountChanged, statisticsView, &StatisticsView::updateMoveCount);
        connect(&puzzleModel, &PuzzleModel::gameSolved, this, [&](){
            gameFinished = true;
            timer->stop();

            int hours = elapsedTime / 3600;
            int minutes = (elapsedTime % 3600) / 60;
            int seconds = elapsedTime % 60;
            QString timeString = QString("Your time: %1:%2:%3").arg(hours, 2, 10, QLatin1Char('0')).arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));

            QString movesString = QString("Moves %1").arg(puzzleModel.getMoveCount());

            QString message = QString("Congratulations! You solved the puzzle.\n%1\n%2").arg(timeString, movesString);

            QMessageBox::information(this, "Puzzle solved!", message);
        });


        elapsedTime = -1;
        timer->start(1000);
        updateTime();

        QThread* thread = new QThread;
        AlgorithmWorker* worker = new AlgorithmWorker(puzzleModel.getBoard());
        worker->moveToThread(thread);
        connect(worker, &AlgorithmWorker::finished, this, &MainWindow::displaySolutions);
        connect(worker, &AlgorithmWorker::finished, worker, &QObject::deleteLater);
        connect(thread, &QThread::finished, thread, &QObject::deleteLater);
        //connect(thread, &QThread::started, worker, &AlgorithmWorker::runAStar); // Możesz uruchomić oba sekwencyjnie lub równolegle
        connect(thread, &QThread::started, worker, &AlgorithmWorker::runIDAStar);
        thread->start();
    });

    connect(boardView, &BoardView::tileClicked, [this](int x, int y) {
        if (gameFinished) {
            return;
        }
        Board board = puzzleModel.getBoard();
        int emptyX = -1, emptyY = -1;
        for (int i = 0; i < board.getSize(); ++i) {
            for (int j = 0; j < board.getSize(); ++j) {
                if (board.getTile(i, j).getValue() == 0) {
                    emptyX = i;
                    emptyY = j;
                    break;
                }
            }
        }

        if ((abs(x - emptyX) == 1 && y == emptyY) || (x == emptyX && abs(y - emptyY) == 1)) {
            if (x > emptyX) { puzzleModel.moveTile(MoveDirection::UP); }
            else if (x < emptyX) { puzzleModel.moveTile(MoveDirection::DOWN); }
            else if (y > emptyY) { puzzleModel.moveTile(MoveDirection::LEFT); }
            else if (y < emptyY) { puzzleModel.moveTile(MoveDirection::RIGHT); }
        }
    });

    connect(&puzzleModel, &PuzzleModel::boardChanged, boardView, &BoardView::updateBoard);
    connect(&puzzleModel, &PuzzleModel::moveCountChanged, statisticsView, &StatisticsView::updateMoveCount);
    connect(&puzzleModel, &PuzzleModel::gameSolved, this, [&](){
        gameFinished = true;
        timer->stop();

        int hours = elapsedTime / 3600;
        int minutes = (elapsedTime % 3600) / 60;
        int seconds = elapsedTime % 60;
        QString timeString = QString("Your time: %1:%2:%3").arg(hours, 2, 10, QLatin1Char('0')).arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));

        QString movesString = QString("Moves %1").arg(puzzleModel.getMoveCount());

        QString message = QString("Congratulations! You solved the puzzle.\n%1\n%2").arg(timeString, movesString);

        QMessageBox::information(this, "Puzzle solved!", message);
    });


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    timer->start(1000);
}

void MainWindow::updateTime() {
    elapsedTime++;
    int hours = elapsedTime / 3600;
    int minutes = (elapsedTime % 3600) / 60;
    int seconds = elapsedTime % 60;
    statisticsView->updateTime(hours, minutes, seconds);
}

std::string moveToString(MoveDirection move) {
    switch (move) {
    case MoveDirection::UP: return "UP";
    case MoveDirection::DOWN: return "DOWN";
    case MoveDirection::LEFT: return "LEFT";
    case MoveDirection::RIGHT: return "RIGHT";
    default: return "";
    }
}

void MainWindow::displaySolutions(std::vector<MoveDirection> aStarMoves, std::vector<MoveDirection> idaStarMoves) {
    QString aStarSolution = "A* Solution: ";
    for (const auto& move : aStarMoves) {
        aStarSolution += QString::fromStdString(moveToString(move)) + " ";
    }

    QString idaStarSolution = "IDA* Solution: ";
    for (const auto& move : idaStarMoves) {
        idaStarSolution += QString::fromStdString(moveToString(move)) + " ";
    }

    QString solutionsText = "Solutions (will disappear in 5 seconds):\n\nA*: " + aStarSolution + "\nIDA*: " + idaStarSolution;

    solutionsDialog = new QDialog(this);
    solutionsDialog->setWindowTitle("Solution Hints");
    QVBoxLayout* dialogLayout = new QVBoxLayout(solutionsDialog);
    QLabel* solutionsLabel = new QLabel(solutionsText, solutionsDialog);
    solutionsLabel->setAlignment(Qt::AlignLeft);
    dialogLayout->addWidget(solutionsLabel);
    solutionsDialog->setLayout(dialogLayout);
    solutionsDialog->setModal(false); // Nie blokuj interakcji z głównym oknem
    solutionsDialog->show();
}
