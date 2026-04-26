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
    explicit GameWindow(int difficulty, QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void onPotatoClicked();
    void onButterClicked();
    void onMilkClicked();
    void onBreadClicked();
    void onLettuceClicked();   // 生菜（原来叫盘子）
    void onMixClicked();
    void onDiscardClicked();
    void onSubmitClicked();
    void updateTimer();
    void onMenuClicked();
    void onContinueGame();
    void onRestartGame();
    void onBackToLobby();

private:
    void updateBowlDisplay();
    void generateNewOrder();
    void endGame();
    void showStarRating();
    QPushButton*menuBtn;
    bool isPaused;

    // UI 控件
    QPushButton *potatoBtn;
    QPushButton *butterBtn;
    QPushButton *milkBtn;
    QPushButton *breadBtn;
    QPushButton *lettuceBtn;
    QPushButton *mixBtn;
    QPushButton *discardBtn;
    QPushButton *submitBtn;

    QLabel *bowlLabel;
    QLabel *orderLabel;
    QLabel *timerLabel;
    QLabel *scoreLabel;

    // 数据
    QStringList currentIngredients;
    QStringList currentOrder;
    int score;
    int completedOrders;
    int timeLeft;
    QTimer *timer;
    int difficulty;

    QStringList extraIngredients;   // 可选食材
};

#endif
