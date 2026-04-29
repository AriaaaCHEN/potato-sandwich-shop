#include "gamewindow.h"
#include <QMessageBox>
#include <QTime>
#include <cstdlib>
#include <ctime>
#include "mainwindow.h"
#include "menuwindow.h"
#include <QFile>
#include <QDataStream>
#include <QTimer>
#include <QLabel>
#include <QPixmap>

GameWindow::GameWindow(int difficulty, QWidget *parent)
    : QMainWindow(parent)
    , isPaused(false)
    , score(0)
    , completedOrders(0)
    , comboCount(0)
    , timeLeft(0)
    , maxScore(0)
    , difficulty(difficulty)


{
    setFixedSize(1054, 768);

    // 背景图
    QPixmap bg(":/images/bg_game.jpg");
    bg = bg.scaled(1054, 768, Qt::KeepAspectRatioByExpanding);
    QLabel *bgLabel = new QLabel(this);
    bgLabel->setPixmap(bg);
    bgLabel->setGeometry(0, 0, 1054, 768);
    bgLabel->lower();

    // 读取最高分
    QFile file("maxscore.dat");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> maxScore;
        file.close();
    } else {
        maxScore = 0;
    }

    // 最高分标签
    maxScoreLabel = new QLabel(this);
    maxScoreLabel->setGeometry(495, 703, 300, 50);
    maxScoreLabel->setStyleSheet(
        "font-size: 32px;"
        "font-weight: bold;"
        "color: #D9534F;"
        "background: transparent;"
        "font-family: 'Courier New', monospace;"
    );
    maxScoreLabel->setText("最高纪录：" + QString::number(maxScore));

    // 随机种子
    std::srand(static_cast<unsigned>(QTime::currentTime().msec()));

    // 根据难度设置倒计时总秒数
    if (difficulty == 1) timeLeft = 60;
    else if (difficulty == 2) timeLeft = 60;
    else timeLeft = 60;


    // 额外食材池
    extraIngredients << "黄油" << "牛奶" << "生菜" <<"鸡腿排";


    // 反馈标签（表情）
    feedbackLabel = new QLabel(this);
    feedbackLabel->setGeometry(500, 80, 200, 40);
    feedbackLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: orange;");
    feedbackLabel->clear();

    // ---------------- 创建控件 ----------------
    // 订单序号标签（左上角）
    serialLabel = new QLabel(this);
    serialLabel->setGeometry(65, 38, 120, 50);
    serialLabel->setStyleSheet(
        "font-size: 32px;"
        "font-weight: bold;"
        "color: #D9534F;"
        "background: transparent;"
        "font-family: 'Courier New', monospace;"
    );
    serialLabel->setAlignment(Qt::AlignCenter);
    serialLabel->setText("第 1 单");

    // 订单内容标签（序号右侧）
    orderContentLabel = new QLabel(this);
    orderContentLabel->setGeometry(180, 38, 350, 50);
    orderContentLabel->setAlignment(Qt::AlignCenter);
    orderContentLabel->setText("土豆泥 + 面包");

    // 倒计时标签（右上角，电子表样式）
    timerLabel = new QLabel(this);
    timerLabel->setGeometry(650, 35, 200, 60);
    timerLabel->setStyleSheet(
        "font-size: 36px;"
        "font-weight: bold;"
        "color: #D9534F;"
        "background: transparent;"
        "font-family: 'Courier New', monospace;"  // 马赛克风格字体
    );
    timerLabel->setAlignment(Qt::AlignCenter);
    timerLabel->setText("01：00");

    // 初始化序号
    orderSerial = 1;
    // 得分控件
    scoreLabel = new QLabel(this);
    scoreLabel->setGeometry(220, 703, 150, 50);
    scoreLabel->setStyleSheet(
        "font-size: 32px;"
        "font-weight: bold;"
        "color: #D9534F;"          // 和倒计时一样的红色
        "background: transparent;"
        "font-family: 'Courier New', monospace;"
    );
    scoreLabel->setText("得分：" + QString::number(score));


    // 食材按钮
    potatoBtn = new QPushButton(this);
    potatoBtn->setGeometry(60, 362, 100, 48);
    potatoBtn->setStyleSheet("border: none; background: transparent;");

    butterBtn = new QPushButton(this);
    butterBtn->setGeometry(185, 362, 100, 48);
    butterBtn->setStyleSheet("border: none; background: transparent;");

    milkBtn = new QPushButton(this);
    milkBtn->setGeometry(300, 362, 90, 48);
    milkBtn->setStyleSheet("border: none; background: transparent;");

    breadBtn = new QPushButton(this);
    breadBtn->setGeometry(420, 362, 90, 48);
    breadBtn->setStyleSheet("border: none; background: transparent;");

    lettuceBtn = new QPushButton(this);
    lettuceBtn->setGeometry(550, 362, 100, 48);
    lettuceBtn->setStyleSheet("border: none; background: transparent;");

    chickenBtn = new QPushButton(this);
    chickenBtn->setGeometry(680, 362, 100, 48);
    chickenBtn->setStyleSheet("border: none; background: transparent;");
    //搅拌
    mixBtn = new QPushButton(this);
    mixBtn->setIcon(QIcon(":/images/btn_mix.png"));
    mixBtn->setIconSize(QSize(100, 50));
    mixBtn->setFixedSize(100, 50);
    mixBtn->setGeometry(50, 600, 100, 50);
    mixBtn->setStyleSheet("border: none; background: transparent;");
    mixBtn->setToolTip("搅拌");

    bowlLabel = new QLabel("碗里：空", this);
    bowlLabel->setGeometry(365, 450, 300, 180);
    bowlLabel->setWordWrap(true);
    bowlLabel->setStyleSheet(
        "font-size: 24px;"
        "font-weight: bold;"
        "color: #D9534F;"
        "background: transparent;"
        "font-family: 'Courier New', monospace;"
    );
    bowlLabel->setAlignment(Qt::AlignCenter);
    //丢弃按钮
    discardBtn = new QPushButton(this);
    discardBtn->setIcon(QIcon(":/images/btn_discard.png"));
    discardBtn->setIconSize(QSize(50, 50));
    discardBtn->setFixedSize(50, 50);
    discardBtn->setGeometry(680, 580, 50, 50);
    discardBtn->setStyleSheet("border: none; background: transparent;");
    discardBtn->setToolTip("丢弃");
    //提交按钮
    submitBtn = new QPushButton(this);
    submitBtn->setGeometry(770, 620, 250, 120);
    submitBtn->setStyleSheet("border: none; background: transparent;");

    //菜单按钮（放在右上角）
    menuBtn=new QPushButton(this);
    menuBtn->setGeometry(932,18,93,93);
    menuBtn->setStyleSheet("border: none; background: transparent;");
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
    connect(chickenBtn, &QPushButton::clicked, this, &GameWindow::onChickenClicked);

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
void GameWindow::onChickenClicked(){ currentIngredients.append("鸡腿排"); updateBowlDisplay(); }

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
        // 连击奖励
        comboCount++;
        if (comboCount >= 5) {
            score += 10;
            feedbackLabel->setText("🔥 超级连击 +10！");
        } else if (comboCount >= 3) {
            score += 5;
            feedbackLabel->setText("⚡ 连击 +5！");
        } else {
            feedbackLabel->setText("😊 美味！");
        }
        feedbackLabel->show();
        QTimer::singleShot(1500, feedbackLabel, &QLabel::hide);// 连击奖励
        completedOrders++;
        QMessageBox::information(this, "成功", "订单完成！+10分");
        currentIngredients.clear();
        updateBowlDisplay();
        generateNewOrder();  // 生成下一个随机订单
        orderSerial++;
        serialLabel->setText(QString("第 %1 单").arg(orderSerial));
        scoreLabel->setText("得分: " + QString::number(score));
    } else {
        // 错误
        score -= 5;
        scoreLabel->setText("得分: " + QString::number(score));
        comboCount = 0;
        feedbackLabel->setText("😭 做错了...");
        feedbackLabel->show();
        QTimer::singleShot(1500, feedbackLabel, &QLabel::hide);
        QMessageBox::warning(this, "错误", "食材不正确，订单失败！-5分");
        currentIngredients.clear();
        updateBowlDisplay();
        // 不生成新订单，玩家可以重做当前订单（订单不变）
        }
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
        QStringList shuffled = extraIngredients;
        for (int i = 0; i < shuffled.size(); ++i) {
            int j = std::rand() % shuffled.size();
            shuffled.swap(i, j);
        }
        for (int i = 0; i < extraCount && i < shuffled.size(); ++i) {
            currentOrder << shuffled[i];
        }
    }

    // 生成订单文字
    QString orderText = "";
    for (int i = 0; i < currentOrder.size(); ++i) {
        if (i > 0) orderText += " + ";
        orderText += currentOrder[i];
    }

    // 动态调整宽度和字体大小
    int textLen = orderText.length();
    if (textLen > 20) {
        orderContentLabel->setGeometry(180, 38, 520, 50);
        orderContentLabel->setStyleSheet(
            "font-size: 18px;"
            "font-weight: bold;"
            "color: #D9534F;"
            "background: transparent;"
            "font-family: 'Courier New', monospace;"
        );
    } else if (textLen > 12) {
        orderContentLabel->setGeometry(180, 38, 450, 50);
        orderContentLabel->setStyleSheet(
            "font-size: 22px;"
            "font-weight: bold;"
            "color: #D9534F;"
            "background: transparent;"
            "font-family: 'Courier New', monospace;"
        );
    } else {
        orderContentLabel->setGeometry(180, 38, 350, 50);
        orderContentLabel->setStyleSheet(
            "font-size: 28px;"
            "font-weight: bold;"
            "color: #D9534F;"
            "background: transparent;"
            "font-family: 'Courier New', monospace;"
        );
    }

    orderContentLabel->setText(orderText);
    orderContentLabel->setAlignment(Qt::AlignCenter);
}

// 倒计时更新
void GameWindow::updateTimer()
{
    if (isPaused) return;

    timeLeft--;
    int minutes = timeLeft / 60;
    int seconds = timeLeft % 60;
    QString timeStr = QString("%1:%2")
                        .arg(minutes, 2, 10, QChar('0'))
                        .arg(seconds, 2, 10, QChar('0'));
    timerLabel->setText(timeStr);

    if (timeLeft <= 0) {
        timer->stop();
        endGame();
    }
}

// 游戏结束
void GameWindow::endGame()
{
    // 保存最高分
    if (score > maxScore) {
        maxScore = score;
        maxScoreLabel->setText("最高纪录：" + QString::number(maxScore));
        QFile file("maxscore.dat");
        if (file.open(QIODevice::WriteOnly)) {
            QDataStream out(&file);
            out << maxScore;
            file.close();
        }
    }
    showStarRating();
    // 返回开始界面（MainWindow）
    this->close();
    MainWindow *mainWin = new MainWindow();
    mainWin->show();
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
        QString("时间到！\n\n完成订单数：%1\n本次分数：%2\n最高分数：%3\n\n%4")
        .arg(completedOrders).arg(score).arg(maxScore).arg(starMsg));
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

    //重置得分
    score = 0;
    scoreLabel->setText("得分: " + QString::number(score));

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
