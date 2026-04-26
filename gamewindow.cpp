#include "gamewindow.h"
#include <QMessageBox>
#include <QTime>
#include <cstdlib>
#include <ctime>
#include"mainwindow.h"
#include"menuwindow.h"

GameWindow::GameWindow(int difficulty, QWidget *parent)
    : QMainWindow(parent)
    ,isPaused(false)
    , score(0)
    , completedOrders(0)
    , difficulty(difficulty)

{
    // 随机种子
    std::srand(static_cast<unsigned>(QTime::currentTime().msec()));

    // 根据难度设置倒计时总秒数
    if (difficulty == 1) timeLeft = 60;
    else if (difficulty == 2) timeLeft = 60;
    else timeLeft = 60;

    setFixedSize(800, 600);

    // 额外食材池（生菜代替盘子）
    extraIngredients << "黄油" << "牛奶" << "生菜";

    // ---------------- 创建控件 ----------------
    orderLabel = new QLabel(this);
    orderLabel->setGeometry(50, 30, 300, 40);
    orderLabel->setStyleSheet("font-size: 16px; border: 2px solid gray; padding: 5px;");

    timerLabel = new QLabel("倒计时：" + QString::number(timeLeft), this);
    timerLabel->setGeometry(600, 30, 150, 40);
    timerLabel->setStyleSheet("font-size: 16px; border: 2px solid gray; padding: 5px;");

    scoreLabel = new QLabel("分数：" + QString::number(score) + "  订单：" + QString::number(completedOrders), this);
    scoreLabel->setGeometry(50, 80, 280, 40);
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

    lettuceBtn = new QPushButton("🥬 生菜", this);
    lettuceBtn->setGeometry(200, 220, 120, 50);

    mixBtn = new QPushButton("🥄 搅拌", this);
    mixBtn->setGeometry(350, 220, 120, 50);

    bowlLabel = new QLabel("碗里：空", this);
    bowlLabel->setGeometry(400, 150, 300, 100);
    bowlLabel->setStyleSheet("border: 3px solid brown; background-color: #FFF8E7; font-size: 14px; padding: 10px;");

    discardBtn = new QPushButton("🗑️ 丢弃", this);
    discardBtn->setGeometry(400, 280, 120, 50);

    submitBtn = new QPushButton("✅ 提交", this);
    submitBtn->setGeometry(580, 280, 120, 50);

    //菜单按钮（放在右上角）
    menuBtn=new QPushButton("📋 菜单",this);
    menuBtn->setGeometry(700,10,80,30);
    connect(menuBtn,&QPushButton::clicked,this,&GameWindow::onMenuClicked);

    // 信号槽连接
    connect(potatoBtn, &QPushButton::clicked, this, &GameWindow::onPotatoClicked);
    connect(butterBtn, &QPushButton::clicked, this, &GameWindow::onButterClicked);
    connect(milkBtn, &QPushButton::clicked, this, &GameWindow::onMilkClicked);
    connect(breadBtn, &QPushButton::clicked, this, &GameWindow::onBreadClicked);
    connect(lettuceBtn, &QPushButton::clicked, this, &GameWindow::onLettuceClicked);
    connect(mixBtn, &QPushButton::clicked, this, &GameWindow::onMixClicked);
    connect(discardBtn, &QPushButton::clicked, this, &GameWindow::onDiscardClicked);
    connect(submitBtn, &QPushButton::clicked, this, &GameWindow::onSubmitClicked);

    // 生成第一个订单
    generateNewOrder();

    // 启动倒计时
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateTimer);
    timer->start(1000);
}

GameWindow::~GameWindow() {}

// 食材点击
void GameWindow::onPotatoClicked() { currentIngredients.append("土豆"); updateBowlDisplay(); }
void GameWindow::onButterClicked() { currentIngredients.append("黄油"); updateBowlDisplay(); }
void GameWindow::onMilkClicked() { currentIngredients.append("牛奶"); updateBowlDisplay(); }
void GameWindow::onBreadClicked() { currentIngredients.append("面包"); updateBowlDisplay(); }
void GameWindow::onLettuceClicked() { currentIngredients.append("生菜"); updateBowlDisplay(); }

// 搅拌：土豆+黄油 -> 土豆泥
void GameWindow::onMixClicked()
{
    if (currentIngredients.contains("土豆") && currentIngredients.contains("黄油")) {
        currentIngredients.removeAll("土豆");
        currentIngredients.removeAll("黄油");
        currentIngredients.append("土豆泥");
        updateBowlDisplay();
        QMessageBox::information(this, "搅拌", "搅拌成功！得到土豆泥。");
    } else {
        QMessageBox::warning(this, "搅拌", "需要土豆和黄油才能搅拌成土豆泥！");
    }
}

void GameWindow::onDiscardClicked()
{
    currentIngredients.clear();
    updateBowlDisplay();
    QMessageBox::information(this, "丢弃", "已清空碗里的食材");
}

// 提交订单
void GameWindow::onSubmitClicked()
{
    // 检查匹配
    bool match = true;
    if (currentIngredients.size() != currentOrder.size()) {
        match = false;
    } else {
        for (const QString& need : currentOrder) {
            if (!currentIngredients.contains(need)) {
                match = false;
                break;
            }
        }
    }

    if (match) {
        // 正确
        score += 10;
        completedOrders++;
        QMessageBox::information(this, "成功", "订单完成！+10分");
        currentIngredients.clear();
        updateBowlDisplay();
        generateNewOrder();  // 生成下一个随机订单
    } else {
        // 错误
        score -= 5;
        QMessageBox::warning(this, "错误", "食材不正确，订单失败！-5分");
        currentIngredients.clear();
        updateBowlDisplay();
        // 不生成新订单，玩家可以重做当前订单（订单不变）
    }

    // 更新显示
    scoreLabel->setText("分数：" + QString::number(score) + "  订单：" + QString::number(completedOrders));
}

// 生成随机订单（基底：土豆泥+面包）
void GameWindow::generateNewOrder()
{
    currentOrder.clear();
    currentOrder << "土豆泥" << "面包";

    int extraCount = 0;
    if (difficulty == 1) extraCount = 0;
    else if (difficulty == 2) extraCount = 1;
    else extraCount = 2;

    if (extraCount > 0) {
        // 随机打乱额外食材列表，取前 extraCount 个
        QStringList shuffled = extraIngredients;
        for (int i = 0; i < shuffled.size(); ++i) {
            int j = std::rand() % shuffled.size();
            shuffled.swap(i, j);
        }
        for (int i = 0; i < extraCount && i < shuffled.size(); ++i) {
            currentOrder << shuffled[i];
        }
    }

    // 显示订单文字
    QString orderText = "订单：";
    for (int i = 0; i < currentOrder.size(); ++i) {
        if (i > 0) orderText += " + ";
        orderText += currentOrder[i];
    }
    orderLabel->setText(orderText);
}

// 倒计时更新
void GameWindow::updateTimer()
{
    if(isPaused)return;

    timeLeft--;
    timerLabel->setText("倒计时：" + QString::number(timeLeft));
    if (timeLeft <= 0) {
        timer->stop();
        endGame();
    }
}

// 游戏结束
void GameWindow::endGame()
{
    showStarRating();
    this->close();
}

// 星级评价
void GameWindow::showStarRating()
{
    int star = 0;
    if (difficulty == 1) {  // 简单
        if (completedOrders >= 5) star = 3;
        else if (completedOrders >= 3) star = 2;
        else if (completedOrders >= 1) star = 1;
    } else if (difficulty == 2) {  // 普通
        if (completedOrders >= 4) star = 3;
        else if (completedOrders >= 2) star = 2;
        else if (completedOrders >= 1) star = 1;
    } else {  // 困难
        if (completedOrders >= 3) star = 3;
        else if (completedOrders >= 2) star = 2;
        else if (completedOrders >= 1) star = 1;
    }

    QString starMsg;
    if (star == 3) starMsg = "⭐⭐⭐ 三星！ 太厉害了！";
    else if (star == 2) starMsg = "⭐⭐ 二星，不错哟！";
    else if (star == 1) starMsg = "⭐ 一星，继续努力！";
    else starMsg = "没有星星，下次再来吧~";

    QMessageBox::information(nullptr, "游戏结束",
        QString("时间到！\n\n完成订单数：%1\n最终分数：%2\n\n%3")
        .arg(completedOrders).arg(score).arg(starMsg));
}

// 更新碗的显示
void GameWindow::updateBowlDisplay()
{
    if (currentIngredients.isEmpty()) {
        bowlLabel->setText("碗里：空");
    } else {
        QString text = "碗里：";
        for (int i = 0; i < currentIngredients.size(); ++i) {
            if (i > 0) text += " + ";
            text += currentIngredients[i];
        }
        bowlLabel->setText(text);
    }
}

void GameWindow::onMenuClicked()
{
    // 暂停游戏
    isPaused = true;
    timer->stop();  // 停止倒计时

    // 创建并显示菜单窗口
    MenuWindow *menuWin = new MenuWindow(this);

    // 连接菜单窗口的信号到当前窗口的槽
    connect(menuWin, &MenuWindow::continueGame, this, &GameWindow::onContinueGame);
    connect(menuWin, &MenuWindow::restartGame, this, &GameWindow::onRestartGame);
    connect(menuWin, &MenuWindow::backToLobby, this, &GameWindow::onBackToLobby);

    // 显示菜单窗口（模态，必须关闭才能回来）
    menuWin->setAttribute(Qt::WA_DeleteOnClose);  // 关闭时自动删除
    menuWin->show();
}

void GameWindow::onContinueGame()
{
    // 恢复游戏
    isPaused = false;
    timer->start(1000);
}

void GameWindow::onRestartGame()
{
    // 重置所有数据
    isPaused = false;

    // 重置分数和订单数
    score = 0;
    completedOrders = 0;
    scoreLabel->setText("分数：0  订单：0");

    // 清空碗
    currentIngredients.clear();
    updateBowlDisplay();

    // 重置时间
    if (difficulty == 1) timeLeft = 30;   // 你自己设的时长
    else if (difficulty == 2) timeLeft = 25;
    else timeLeft = 20;
    timerLabel->setText("倒计时：" + QString::number(timeLeft));

    // 重新生成订单
    generateNewOrder();

    // 重启计时器
    timer->start(1000);
}

void GameWindow::onBackToLobby()
{
    // 关闭当前游戏窗口
    this->close();

    // 重新打开难度选择窗口（MainWindow 已经有一个，先关闭旧的？这里简化：直接开新的）
    MainWindow *mainWin = new MainWindow();
    mainWin->show();
}
