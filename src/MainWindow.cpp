#include "MainWindow.h"
#include "GameState.h"

#include <QFileDialog>
#include <QStatusBar>

MainWindow::MainWindow(int size, QWidget *parent) : QMainWindow(parent), puzzleModel(size) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QGridLayout *layout = new QGridLayout(centralWidget);

    boardView = new BoardView(puzzleModel.getBoard(), this);
    statisticsView = new StatisticsView(this);

    QPushButton *newGameButton = new QPushButton("New Game", this);
    QPushButton *saveGameButton = new QPushButton("Save Game", this);
    QPushButton *loadGameButton = new QPushButton("Load Game", this);
    QPushButton *closeGameButton = new QPushButton("Quit", this);
    QLabel *boardSizeLabel = new QLabel("Board size", this);
    boardSizeComboBox = new QComboBox(this);
    boardSizeComboBox->addItem("3x3");
    boardSizeComboBox->addItem("4x4");
    boardSizeComboBox->addItem("5x5");
    boardSizeComboBox->addItem("6x6");
    boardSizeComboBox->addItem("7x7");
    boardSizeComboBox->addItem("8x8");
    boardSizeComboBox->addItem("9x9");
    boardSizeComboBox->addItem("10x10");
    boardSizeComboBox->addItem("15x15");
    boardSizeComboBox->setCurrentText(QString::number(size) + "x" + QString::number(size));

    QString buttonStyle = "QPushButton {"
                          "    background-color: #4d80e4;"
                          "    background-image: linear-gradient(to bottom, #6699ff, #4d80e4);"
                          "    color: white;"
                          "    border: 1px solid #336699;"
                          "    border-radius: 8px;"
                          "    padding: 10px 20px;"
                          "    font-size: 16px;"
                          "    cursor: pointer;"
                          "    width: 150px;"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: #5e99f2;"
                          "    background-image: linear-gradient(to bottom, #7ab2ff, #5e99f2);"
                          "    border-color: #29527a; "
                          "}";

    newGameButton->setStyleSheet(buttonStyle);
    saveGameButton->setStyleSheet(buttonStyle);
    loadGameButton->setStyleSheet(buttonStyle);
    closeGameButton->setStyleSheet(buttonStyle);

    QString comboBoxStyle = "QComboBox {"
                            "    background-color: white;"
                            "    color: black;"
                            "    border: 1px solid #c0c0c0;"
                            "    border-radius: 5px;"
                            "    padding: 5px 10px;"
                            "    font-size: 14px;"
                            "}"
                            "QComboBox::drop-down {"
                            "    width: 20px;"
                            "}"
                            "QComboBox QAbstractItemView {"
                            "    border: 1px solid #c0c0c0;"
                            "    selection-background-color: #4d80e4;"
                            "    selection-color: white;"
                            "}";

    boardSizeComboBox->setStyleSheet(comboBoxStyle);

    layout->addWidget(boardView, 0, 0, -1, 1);

    int rightColumn = 1;
    int startRow = 5;

    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), 0, rightColumn, startRow, 1);

    layout->addWidget(newGameButton, startRow, rightColumn, 1, 1);
    layout->addWidget(saveGameButton, startRow + 1, rightColumn, 1, 1);
    layout->addWidget(loadGameButton, startRow + 2, rightColumn, 1, 1);
    layout->addWidget(boardSizeLabel, startRow + 3, rightColumn, 1, 1);
    layout->addWidget(boardSizeComboBox, startRow + 4, rightColumn, 1, 1);
    layout->addWidget(statisticsView, startRow + 5, rightColumn, 1, 1);
    layout->addWidget(closeGameButton, startRow + 6, rightColumn, 1, 1);

    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding), startRow + 6, rightColumn, -1, 1);

    centralWidget->setLayout(layout);

    connect(closeGameButton, &QPushButton::clicked, this, &QMainWindow::close);

    connect(saveGameButton, &QPushButton::clicked, [this](){
        saveGame();
    });

    connect(loadGameButton, &QPushButton::clicked, [this](){
        loadGame();
    });

    connect(newGameButton, &QPushButton::clicked, [this, layout](){
        this->gameFinished = false;

        int xPosition = boardSizeComboBox->currentText().indexOf('x');
        int newSize = boardSizeComboBox->currentText().left(xPosition).toInt();

        puzzleModel.~PuzzleModel();

        new (&puzzleModel) PuzzleModel(newSize, this);

        puzzleModel.shuffle();
        statisticsView->updateMoveCount(0);

        delete boardView;
        boardView = new BoardView(puzzleModel.getBoard(), this);
        layout->addWidget(boardView, 0, 0, -1, 1);

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
                if (x < emptyX) { puzzleModel.moveTile(MoveDirection::UP); }
                else if (x > emptyX) { puzzleModel.moveTile(MoveDirection::DOWN); }
                else if (y < emptyY) { puzzleModel.moveTile(MoveDirection::LEFT); }
                else if (y > emptyY) { puzzleModel.moveTile(MoveDirection::RIGHT); }
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
            if (x < emptyX) { puzzleModel.moveTile(MoveDirection::UP); }
            else if (x > emptyX) { puzzleModel.moveTile(MoveDirection::DOWN); }
            else if (y < emptyY) { puzzleModel.moveTile(MoveDirection::LEFT); }
            else if (y > emptyY) { puzzleModel.moveTile(MoveDirection::RIGHT); }
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

void MainWindow::saveGame() {
    QString filename = QFileDialog::getSaveFileName(this, "Save game state", "", "Game State (*.sav)");
    if (!filename.isEmpty()) {
        GameState::save(filename.toStdString(), puzzleModel.getBoard().getSize(), puzzleModel.getBoard(), elapsedTime, puzzleModel.getMoveCount());
    }
}

void MainWindow::loadGame() {
    QString filename = QFileDialog::getOpenFileName(this, "Load game state", "", "Game State (*.sav)");
    if (!filename.isEmpty()) {
        int loadedSize;
        Board loadedBoard(puzzleModel.getBoard().getSize());
        int loadedTime;
        int loadedMoveCount;
        if (GameState::load(filename.toStdString(), loadedSize, loadedBoard, loadedTime, loadedMoveCount)) {
            if (loadedSize != puzzleModel.getBoard().getSize()) {
                puzzleModel.~PuzzleModel();
                new (&puzzleModel) PuzzleModel(loadedSize, this);
                delete boardView;
                boardView = new BoardView(puzzleModel.getBoard(), this);
                qobject_cast<QGridLayout*>(centralWidget()->layout())->addWidget(boardView, 0, 0, 1, 1);
            }
            puzzleModel.setBoard(loadedBoard);
            puzzleModel.setMoveCount(loadedMoveCount);
            elapsedTime = loadedTime;
            gameFinished = false;
            boardView->updateBoard(puzzleModel.getBoard());
            statisticsView->updateMoveCount(puzzleModel.getMoveCount());
            int hours = elapsedTime / 3600;
            int minutes = (elapsedTime % 3600) / 60;
            int seconds = elapsedTime % 60;
            statisticsView->updateTime(hours, minutes, seconds);
        } else {
            QMessageBox::critical(this, "Loading error", "Can't load game state from file.");
        }
    }
}
