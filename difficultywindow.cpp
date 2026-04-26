#include "difficultywindow.h"
#include "gamewindow.h"
#include "mainwindow.h"

DifficultyWindow::DifficultyWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(700, 700);

    // ========= 背景图 =========
    QPixmap bg(":/images/bg_difficulty.jpg");
    bg = bg.scaled(700, 700, Qt::KeepAspectRatioByExpanding);
    QLabel *bgLabel = new QLabel(this);
    bgLabel->setPixmap(bg);
    bgLabel->setGeometry(0, 0, 700, 700);
    bgLabel->lower();
    // ========= 难度选择按钮 =========
    simpleBtn = new QPushButton(this);
    simpleBtn->setIcon(QIcon(":/images/btn_simple.png"));
    simpleBtn->setIconSize(QSize(240, 60));
    simpleBtn->setFixedSize(240, 60);
    simpleBtn->setGeometry(245, 230, 200, 60);
    simpleBtn->setStyleSheet("border: none; background: transparent;");

    normalBtn = new QPushButton(this);
    normalBtn->setIcon(QIcon(":/images/btn_normal.png"));
    normalBtn->setIconSize(QSize(240, 60));
    normalBtn->setFixedSize(240, 60);
    normalBtn->setGeometry(245, 310, 200, 60);
    normalBtn->setStyleSheet("border: none; background: transparent;");

    hardBtn = new QPushButton(this);
    hardBtn->setIcon(QIcon(":/images/btn_hard.png"));
    hardBtn->setIconSize(QSize(240, 60));
    hardBtn->setFixedSize(240, 60);
    hardBtn->setGeometry(245, 390, 200, 60);
    hardBtn->setStyleSheet("border: none; background: transparent;");

    connect(simpleBtn, &QPushButton::clicked, this, &DifficultyWindow::onSimpleClicked);
    connect(normalBtn, &QPushButton::clicked, this, &DifficultyWindow::onNormalClicked);
    connect(hardBtn, &QPushButton::clicked, this, &DifficultyWindow::onHardClicked);

     // ========= 返回大厅按钮 =========
    backBtn = new QPushButton(this);
    backBtn->setIcon(QIcon(":/images/btn_back.png"));
    backBtn->setIconSize(QSize(80, 40));
    backBtn->setFixedSize(80, 40);
    backBtn->setGeometry(600, 640, 80, 40);
    backBtn->setStyleSheet("border: none; background: transparent;");
    connect(backBtn, &QPushButton::clicked, this, &DifficultyWindow::onBackClicked);
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

void DifficultyWindow::onBackClicked()
{
    // 关闭当前难度选择窗口
    this->close();

    // 重新打开 MainWindow（开始界面）
    MainWindow *mainWin = new MainWindow();
    mainWin->show();
}
