#include "difficultywindow.h"
#include "gamewindow.h"

DifficultyWindow::DifficultyWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(800, 600);

    simpleBtn = new QPushButton("简单模式", this);
    simpleBtn->setGeometry(300, 200, 200, 60);

    normalBtn = new QPushButton("普通模式", this);
    normalBtn->setGeometry(300, 280, 200, 60);

    hardBtn = new QPushButton("困难模式", this);
    hardBtn->setGeometry(300, 360, 200, 60);

    connect(simpleBtn, &QPushButton::clicked, this, &DifficultyWindow::onSimpleClicked);
    connect(normalBtn, &QPushButton::clicked, this, &DifficultyWindow::onNormalClicked);
    connect(hardBtn, &QPushButton::clicked, this, &DifficultyWindow::onHardClicked);
}

DifficultyWindow::~DifficultyWindow() {}

void DifficultyWindow::onSimpleClicked()
{
    GameWindow *game = new GameWindow(1);
    game->show();
    this->close();
}

void DifficultyWindow::onNormalClicked()
{
    GameWindow *game = new GameWindow(2);
    game->show();
    this->close();
}

void DifficultyWindow::onHardClicked()
{
    GameWindow *game = new GameWindow(3);
    game->show();
    this->close();
}
