#include "mainwindow.h"
#include "difficultywindow.h"   // 后面要创建的头文件
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(800, 600);

    startBtn = new QPushButton("开始游戏", this);
    startBtn->setGeometry(300, 200, 200, 60);

    introBtn = new QPushButton("游戏简介", this);
    introBtn->setGeometry(300, 280, 200, 60);

    exitBtn = new QPushButton("退出游戏", this);
    exitBtn->setGeometry(300, 360, 200, 60);

    connect(startBtn, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(introBtn, &QPushButton::clicked, this, &MainWindow::onIntroClicked);
    connect(exitBtn, &QPushButton::clicked, this, &MainWindow::onExitClicked);
}

MainWindow::~MainWindow() {}

void MainWindow::onStartClicked()
{
    DifficultyWindow *diffWin = new DifficultyWindow();
    diffWin->show();
    this->close();
}

void MainWindow::onIntroClicked()
{
    QMessageBox::information(this, "游戏简介",
        "欢迎来到吉伊卡哇土豆泥三明治店！\n\n"
        "制作土豆泥三明治，完成订单。\n"
        "难度越高，需要的配料越多。");
}

void MainWindow::onExitClicked()
{
    close();
}
