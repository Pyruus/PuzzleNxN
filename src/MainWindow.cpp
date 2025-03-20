#include "../include/MainWindow.h"

MainWindow::MainWindow(int size, QWidget *parent)
    : QMainWindow(parent)
{
    board = new Board(size);
    setupUI();
    createPuzzle();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI(){
    centralWidget = new QWidget();
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    gridLayout = new QGridLayout();
    gridLayout->setSpacing(5);

    buttonLayout = new QHBoxLayout();

    moveCountLabel = new QLabel("Moves: 0");
    newGameButton = new QPushButton("New Game");
    sizeComboBox = new QComboBox();
    sizeComboBox->addItem("3x3");
    sizeComboBox->addItem("4x4");
    sizeComboBox->addItem("5x5");
    sizeComboBox->setCurrentIndex(board->getGridSize() - 3);

    buttonLayout->addWidget(moveCountLabel);
    buttonLayout->addWidget(sizeComboBox);
    buttonLayout->addWidget(newGameButton);

    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(buttonLayout);
}

void MainWindow::createPuzzle(){
    for (int i = 0; i < board->getGridSize() * board->getGridSize(); i++){
        QPushButton *tile = new QPushButton();
        tile->setFixedSize(80, 80);
        QFont font = tile->font();
        font.setPointSize(16);
        tile->setFont(font);

        if (board->getTiles()[i]->getValue() != 0) {
            tile->setText(QString::number(board->getTiles()[i]->getValue()));
        } else {
            tile->setVisible(false);
        }

        gridLayout->addWidget(tile, i / board->getGridSize(), i % board->getGridSize());
    }
}
