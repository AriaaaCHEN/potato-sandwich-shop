#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QStringList>

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void onPotatoClicked();   // 加土豆
    void onButterClicked();   // 加黄油
    void onMilkClicked();     // 加牛奶
    void onBreadClicked();    // 加面包
    void onPlateClicked();    // 加盘子
    void onMixClicked();      // 搅拌
    void onDiscardClicked();  // 丢弃
    void onSubmitClicked();   // 提交
    void updateTimer();       // 倒计时更新

private:
    void updateBowlDisplay();  // 更新碗的显示（这一行之前缺了）

    // UI控件
    QPushButton *potatoBtn;
    QPushButton *butterBtn;
    QPushButton *milkBtn;
    QPushButton *breadBtn;
    QPushButton *plateBtn;
    QPushButton *mixBtn;
    QPushButton *discardBtn;
    QPushButton *submitBtn;

    QLabel *bowlLabel;        // 显示碗里的食材
    QLabel *orderLabel;       // 显示当前订单
    QLabel *timerLabel;       // 显示倒计时
    QLabel *scoreLabel;       // 显示分数

    // 游戏数据
    QStringList currentIngredients;  // 碗里当前的食材
    QStringList currentOrder;        // 当前订单需要的食材
    int score;                       // 当前分数
    int timeLeft;                    // 剩余时间
    QTimer *timer;                   // 倒计时器
};

#endif
