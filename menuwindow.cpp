#include "menuwindow.h"
#include <QVBoxLayout>

MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(400, 300);
    setWindowTitle("游戏菜单");

    // 创建一个中心控件和布局
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *layout = new QVBoxLayout(central);

    // 创建三个按钮
    continueBtn = new QPushButton("继续游戏", this);
    restartBtn = new QPushButton("重新开始", this);
    backBtn = new QPushButton("返回大厅", this);

    // 设置按钮大小
    continueBtn->setFixedSize(200, 50);
    restartBtn->setFixedSize(200, 50);
    backBtn->setFixedSize(200, 50);

    // 添加到布局并居中
    layout->addWidget(continueBtn, 0, Qt::AlignCenter);
    layout->addWidget(restartBtn, 0, Qt::AlignCenter);
    layout->addWidget(backBtn, 0, Qt::AlignCenter);

    // 连接信号槽
    connect(continueBtn, &QPushButton::clicked, this, &MenuWindow::onContinueClicked);
    connect(restartBtn, &QPushButton::clicked, this, &MenuWindow::onRestartClicked);
    connect(backBtn, &QPushButton::clicked, this, &MenuWindow::onBackClicked);
}

MenuWindow::~MenuWindow() {}

void MenuWindow::onContinueClicked()
{
    emit continueGame();  // 发射信号
    this->close();        // 关闭菜单窗口
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
