#include "mainwindow.h"
#include "gamewindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(800, 600);

    // 开始游戏按钮
    startBtn = new QPushButton("开始游戏", this);
    startBtn->setGeometry(300, 200, 200, 60);

    // 游戏简介按钮
    introBtn = new QPushButton("游戏简介", this);
    introBtn->setGeometry(300, 280, 200, 60);

    // 退出游戏按钮
    exitBtn = new QPushButton("退出游戏", this);
    exitBtn->setGeometry(300, 360, 200, 60);

    // 连接信号槽
    connect(startBtn, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(introBtn, &QPushButton::clicked, this, &MainWindow::onIntroClicked);
    connect(exitBtn, &QPushButton::clicked, this, &MainWindow::onExitClicked);
}

MainWindow::~MainWindow()
{
}

// 开始游戏：打开游戏窗口，关闭当前窗口
void MainWindow::onStartClicked()
{
    GameWindow *gameWin = new GameWindow();
    gameWin->show();
    this->close();
}

// 游戏简介：弹窗显示说明
void MainWindow::onIntroClicked()
{
    QMessageBox::information(this, "游戏简介",
        "欢迎来到吉伊卡哇三明治工坊！\n\n"
        "点击食材加入碗中，搅拌后提交订单。\n"
        "在规定时间内完成尽可能多的订单！");
}

// 退出游戏：关闭程序
void MainWindow::onExitClicked()
{
    this->close();
}
