#include "../include/ControlPanel.h"
#include <QPushButton>
#include <QGridLayout>

ControlPanel::ControlPanel(QWidget *parent) : QWidget(parent) {
    QGridLayout *layout = new QGridLayout(this);

    QPushButton *shuffleButton = new QPushButton("Shuffle", this);
    QPushButton *upButton = new QPushButton("Up", this);
    QPushButton *downButton = new QPushButton("Down", this);
    QPushButton *leftButton = new QPushButton("Left", this);
    QPushButton *rightButton = new QPushButton("Right", this);

    layout->addWidget(shuffleButton, 0, 0, 1, 2);
    layout->addWidget(upButton, 1, 1);
    layout->addWidget(downButton, 3, 1);
    layout->addWidget(leftButton, 2, 0);
    layout->addWidget(rightButton, 2, 2);

    connect(shuffleButton, &QPushButton::clicked, this, &ControlPanel::shuffleClicked);
    connect(upButton, &QPushButton::clicked, this, &ControlPanel::moveUpClicked);
    connect(downButton, &QPushButton::clicked, this, &ControlPanel::moveDownClicked);
    connect(leftButton, &QPushButton::clicked, this, &ControlPanel::moveLeftClicked);
    connect(rightButton, &QPushButton::clicked, this, &ControlPanel::moveRightClicked);
}
