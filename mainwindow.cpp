#include "mainwindow.h"
#include "difficultywindow.h"   // 后面要创建的头文件
#include <QMessageBox>
#include <QLabel>
#include "introwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1054, 768);

    // ========= 背景图 =========
    QPixmap bg(":/images/bg_start.jpg");
    bg = bg.scaled(1054, 768, Qt::KeepAspectRatioByExpanding);
    QLabel *bgLabel = new QLabel(this);
    bgLabel->setPixmap(bg);
    bgLabel->setGeometry(0, 0, 1054, 768);
    bgLabel->lower();
    // ========= 图片按钮 =========
    startBtn = new QPushButton(this);
    startBtn->setIcon(QIcon(":/images/btn_start.png"));
    startBtn->setIconSize(QSize(240, 60));
    startBtn->setFixedSize(240, 60);
    startBtn->setGeometry(407, 300, 300, 60);
    startBtn->setStyleSheet("border: none; background: transparent;");

    introBtn = new QPushButton(this);
    introBtn->setIcon(QIcon(":/images/btn_intro.png"));
    introBtn->setIconSize(QSize(240, 60));
    introBtn->setFixedSize(240, 60);
    introBtn->setGeometry(407, 390, 300, 60);
    introBtn->setStyleSheet("border: none; background: transparent;");

    exitBtn = new QPushButton(this);
    exitBtn->setIcon(QIcon(":/images/btn_exit.png"));
    exitBtn->setIconSize(QSize(240, 60));
    exitBtn->setFixedSize(240, 60);
    exitBtn->setGeometry(407, 480, 300, 60);
    exitBtn->setStyleSheet("border: none; background: transparent;");
    // ========= 对应信号槽=========
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
    IntroWindow *intro = new IntroWindow(this);
    intro->show();
}

void MainWindow::onExitClicked()
{
    close();
}
