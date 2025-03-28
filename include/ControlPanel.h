#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>

class ControlPanel : public QWidget {
    Q_OBJECT

public:
    ControlPanel(QWidget *parent = nullptr);

signals:
    void shuffleClicked();
    void moveUpClicked();
    void moveDownClicked();
    void moveLeftClicked();
    void moveRightClicked();
};

#endif // CONTROLPANEL_H
