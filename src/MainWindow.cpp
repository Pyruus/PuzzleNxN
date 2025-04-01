#include "../include/MainWindow.h"

MainWindow::MainWindow(int size, QWidget *parent) : QMainWindow(parent), puzzleModel(size) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QGridLayout *layout = new QGridLayout(centralWidget);

    boardView = new BoardView(puzzleModel.getBoard(), this);
    controlPanel = new ControlPanel(this);

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

    connect(newGameButton, &QPushButton::clicked, [this, layout](){
        int newSize = boardSizeComboBox->currentText().left(1).toInt();

        puzzleModel.~PuzzleModel();

        new (&puzzleModel) PuzzleModel(newSize, this);

        delete boardView;
        boardView = new BoardView(puzzleModel.getBoard(), this);
        layout->addWidget(boardView, 0, 0, 1, 1);

        connect(boardView, &BoardView::tileClicked, [this](int x, int y) {
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
    });

    connect(boardView, &BoardView::tileClicked, [this](int x, int y) {
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
}
