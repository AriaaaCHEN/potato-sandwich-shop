#include "gamewindow.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDebug>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , score(0)
    , timeLeft(60)
{
    setFixedSize(800, 600);

    // ==================== 创建控件 ====================

    // 订单显示
    orderLabel = new QLabel("当前订单：暂无", this);
    orderLabel->setGeometry(50, 30, 300, 40);
    orderLabel->setStyleSheet("font-size: 16px; border: 2px solid gray; padding: 5px;");

    // 倒计时显示
    timerLabel = new QLabel("倒计时：" + QString::number(timeLeft), this);
    timerLabel->setGeometry(600, 30, 150, 40);
    timerLabel->setStyleSheet("font-size: 16px; border: 2px solid gray; padding: 5px;");

    // 分数显示
    scoreLabel = new QLabel("分数：" + QString::number(score), this);
    scoreLabel->setGeometry(50, 80, 150, 40);
    scoreLabel->setStyleSheet("font-size: 16px; border: 2px solid gray; padding: 5px;");

    // 食材按钮
    potatoBtn = new QPushButton("🥔 土豆", this);
    potatoBtn->setGeometry(50, 150, 120, 50);

    butterBtn = new QPushButton("🧈 黄油", this);
    butterBtn->setGeometry(200, 150, 120, 50);

    milkBtn = new QPushButton("🥛 牛奶", this);
    milkBtn->setGeometry(350, 150, 120, 50);

    breadBtn = new QPushButton("🍞 面包", this);
    breadBtn->setGeometry(50, 220, 120, 50);

    plateBtn = new QPushButton("🍽️ 盘子", this);
    plateBtn->setGeometry(200, 220, 120, 50);

    // 搅拌按钮
    mixBtn = new QPushButton("🥄 搅拌", this);
    mixBtn->setGeometry(350, 220, 120, 50);

    // 碗显示区
    bowlLabel = new QLabel("碗里：空", this);
    bowlLabel->setGeometry(500, 150, 230, 120);
    bowlLabel->setStyleSheet("border: 3px solid brown; background-color: #FFF8E7; font-size: 14px; padding: 10px;");

    // 丢弃和提交按钮
    discardBtn = new QPushButton("🗑️ 丢弃", this);
    discardBtn->setGeometry(400, 280, 120, 50);

    submitBtn = new QPushButton("✅ 提交", this);
    submitBtn->setGeometry(580, 280, 120, 50);

    // ==================== 连接信号槽 ====================

    connect(potatoBtn, &QPushButton::clicked, this, &GameWindow::onPotatoClicked);
    connect(butterBtn, &QPushButton::clicked, this, &GameWindow::onButterClicked);
    connect(milkBtn, &QPushButton::clicked, this, &GameWindow::onMilkClicked);
    connect(breadBtn, &QPushButton::clicked, this, &GameWindow::onBreadClicked);
    connect(plateBtn, &QPushButton::clicked, this, &GameWindow::onPlateClicked);
    connect(mixBtn, &QPushButton::clicked, this, &GameWindow::onMixClicked);
    connect(discardBtn, &QPushButton::clicked, this, &GameWindow::onDiscardClicked);
    connect(submitBtn, &QPushButton::clicked, this, &GameWindow::onSubmitClicked);

    // ==================== 初始化游戏 ====================

    // 设置第一个订单（Qt 5.9.2 兼容写法）
    currentOrder.append("土豆");
    currentOrder.append("黄油");
    orderLabel->setText("当前订单：土豆 + 黄油");

    // 启动倒计时
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateTimer);
    timer->start(1000);  // 每秒触发一次
}

GameWindow::~GameWindow()
{
}

// 点击土豆
void GameWindow::onPotatoClicked()
{
    currentIngredients.append("土豆");
    updateBowlDisplay();
}

// 点击黄油
void GameWindow::onButterClicked()
{
    currentIngredients.append("黄油");
    updateBowlDisplay();
}

// 点击牛奶
void GameWindow::onMilkClicked()
{
    currentIngredients.append("牛奶");
    updateBowlDisplay();
}

// 点击面包
void GameWindow::onBreadClicked()
{
    currentIngredients.append("面包");
    updateBowlDisplay();
}

// 点击盘子
void GameWindow::onPlateClicked()
{
    currentIngredients.append("盘子");
    updateBowlDisplay();
}

// 搅拌
void GameWindow::onMixClicked()
{
    if (currentIngredients.contains("土豆") && currentIngredients.contains("黄油")) {
        QMessageBox::information(this, "搅拌", "搅拌成功！变成了土豆泥！");
        // 移除土豆和黄油，加入土豆泥
        currentIngredients.removeAll("土豆");
        currentIngredients.removeAll("黄油");
        currentIngredients.append("土豆泥");
        updateBowlDisplay();
    } else {
        QMessageBox::warning(this, "搅拌", "缺少土豆或黄油，无法搅拌成土豆泥！");
    }
}

// 丢弃
void GameWindow::onDiscardClicked()
{
    currentIngredients.clear();
    updateBowlDisplay();
    QMessageBox::information(this, "丢弃", "已清空碗里的食材");
}

// 提交
void GameWindow::onSubmitClicked()
{
    // 检查碗里的食材是否匹配订单
    bool match = true;

    // 检查订单中的每个食材是否都在碗里
    for (int i = 0; i < currentOrder.size(); i++) {
        if (!currentIngredients.contains(currentOrder[i])) {
            match = false;
            break;
        }
    }

    // 还要检查数量是否相等（没有多余食材）
    if (match && currentIngredients.size() == currentOrder.size()) {
        // 正确
        score += 10;
        scoreLabel->setText("分数：" + QString::number(score));
        QMessageBox::information(this, "成功", "订单完成！+10分");

        // 清空碗
        currentIngredients.clear();
        updateBowlDisplay();

        // 生成新订单（暂时固定）
        currentOrder.clear();
        currentOrder.append("土豆");
        currentOrder.append("黄油");
        orderLabel->setText("当前订单：土豆 + 黄油");

    } else {
        // 错误
        QMessageBox::warning(this, "错误", "食材不正确，订单失败！-5分");
        score -= 5;
        scoreLabel->setText("分数：" + QString::number(score));

        // 清空碗
        currentIngredients.clear();
        updateBowlDisplay();
    }
}

// 更新碗的显示
void GameWindow::updateBowlDisplay()
{
    if (currentIngredients.isEmpty()) {
        bowlLabel->setText("碗里：空");
    } else {
        QString text = "碗里：";
        for (int i = 0; i < currentIngredients.size(); i++) {
            if (i > 0) text += " + ";
            text += currentIngredients[i];
        }
        bowlLabel->setText(text);
    }
}

// 倒计时更新
void GameWindow::updateTimer()
{
    timeLeft--;
    timerLabel->setText("倒计时：" + QString::number(timeLeft));

    if (timeLeft <= 0) {
        timer->stop();
        QMessageBox::information(this, "游戏结束", "时间到！\n最终分数：" + QString::number(score));
        this->close();
    }
}
