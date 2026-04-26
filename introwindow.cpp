#include "introwindow.h"
#include <QVBoxLayout>
#include <QWidget>

IntroWindow::IntroWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 和 mainwindow 一样大
    setFixedSize(1054, 768);
    setWindowTitle("游戏简介");

    // ========= 背景图 =========
    QPixmap bg(":/images/bg_intro.jpg");
    bg = bg.scaled(1054, 768, Qt::KeepAspectRatioByExpanding);
    QLabel *bgLabel = new QLabel(this);
    bgLabel->setPixmap(bg);
    bgLabel->setGeometry(0, 0, 1054, 768);
    bgLabel->lower();
    // 创建中央控件
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setSpacing(25);
    mainLayout->setContentsMargins(60, 0, 60, 50);

    // ========= 标题 =========
    titleLabel = new QLabel(this);
    titleLabel->setText("🍞 吉伊卡哇土豆泥三明治店 🥔");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "font-size: 34px;"
        "font-weight: bold;"
        "color: #8B4513;"
        "font-family: 'Courier New', monospace;"
        "padding: 15px;"
    );
    mainLayout->addWidget(titleLabel);

    // ========= 简介文字 =========
    textLabel = new QLabel(this);
    textLabel->setWordWrap(true);
    textLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    textLabel->setStyleSheet(
        "font-size: 23px;"
        "font-family: 'Courier New', monospace;"
        "color: #3E2723;"
        "background-color: transparent;"
        "padding: 20px;"
        "line-height: 1.8;"
    );

    textLabel->setText(
        "   【游戏目标】\n"
        "   按照顾客订单，制作完美的『土豆泥三明治』！\n\n"
        "   【如何玩】\n"
        "   ① 点击【土豆】+【黄油】 → 再点【搅拌】 → 得到【土豆泥】\n"
        "   ② 加入【面包】 + 【随机食材】\n"
        "   ③ 点击【提交】完成订单！\n"
        "   ④ 做错可点【丢弃】重新开始\n\n"
        "   【难度说明】\n"
        "   ⭐ 简单：土豆泥 + 面包\n"
        "   ⭐⭐ 普通：+ 1种随机食材（牛奶 / 黄油 / 生菜）\n"
        "   ⭐⭐⭐ 困难：+ 2种随机食材，更刺激！\n\n"
        "   ✨ 连击越多，奖励越多！\n"
        "   🏆 最高分会保存在本地！\n\n"
        "   🐱 快来帮吉伊做三明治吧！🍞"
    );

    mainLayout->addWidget(textLabel);

    // ========= 关闭按钮 =========
    closeBtn = new QPushButton(this);
    closeBtn->setIcon(QIcon(":/images/btn_close.png"));
    closeBtn->setIconSize(QSize(160, 50));
    closeBtn->setFixedSize(160, 50);
    closeBtn->setStyleSheet("border: none; background: transparent;");
    connect(closeBtn, &QPushButton::clicked, this, &IntroWindow::onCloseClicked);

    // 按钮居中
    QVBoxLayout *btnLayout = new QVBoxLayout();
    btnLayout->addWidget(closeBtn, 0, Qt::AlignCenter);
    mainLayout->addLayout(btnLayout);
}

IntroWindow::~IntroWindow() {}

void IntroWindow::onCloseClicked()
{
    this->close();
}
