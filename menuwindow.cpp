#include "menuwindow.h"
#include <QLabel>
#include <QPixmap>

MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(450, 450);
    setWindowTitle("游戏菜单");

    // ========== 背景图 ==========
    QPixmap bg(":/images/bg_menu.jpg");
    bg = bg.scaled(450, 450, Qt::KeepAspectRatioByExpanding);
    QLabel *bgLabel = new QLabel(this);
    bgLabel->setPixmap(bg);
    bgLabel->setGeometry(0, 0, 450, 450);
    bgLabel->lower();

    // ========== 三个图片按钮 ==========
    // 继续游戏按钮
    continueBtn = new QPushButton(this);
    continueBtn->setIcon(QIcon(":/images/btn_continue.png"));
    continueBtn->setIconSize(QSize(200, 50));
    continueBtn->setFixedSize(200, 50);
    continueBtn->setGeometry(125, 120, 200, 50);
    continueBtn->setStyleSheet("border: none; background: transparent;");

    // 重新开始按钮
    restartBtn = new QPushButton(this);
    restartBtn->setIcon(QIcon(":/images/btn_restart.png"));
    restartBtn->setIconSize(QSize(200, 50));
    restartBtn->setFixedSize(200, 50);
    restartBtn->setGeometry(125, 200, 200, 50);
    restartBtn->setStyleSheet("border: none; background: transparent;");

    // 返回大厅按钮
    backBtn = new QPushButton(this);
    backBtn->setIcon(QIcon(":/images/btn_back2.png"));
    backBtn->setIconSize(QSize(200, 50));
    backBtn->setFixedSize(200, 50);
    backBtn->setGeometry(125, 280, 200, 50);
    backBtn->setStyleSheet("border: none; background: transparent;");

    // ========== 信号槽连接 ==========
    connect(continueBtn, &QPushButton::clicked, this, &MenuWindow::onContinueClicked);
    connect(restartBtn, &QPushButton::clicked, this, &MenuWindow::onRestartClicked);
    connect(backBtn, &QPushButton::clicked, this, &MenuWindow::onBackClicked);
}

MenuWindow::~MenuWindow() {}

void MenuWindow::onContinueClicked()
{
    emit continueGame();
    this->close();
}

void MenuWindow::onRestartClicked()
{
    emit restartGame();
    this->close();
}

void MenuWindow::onBackClicked()
{
    emit backToLobby();
    this->close();
}
