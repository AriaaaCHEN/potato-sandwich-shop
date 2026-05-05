#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QStringList>
#include <QPixmap>

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
    void onLettuceClicked();
    void onChickenClicked();
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
    void showToastImage(const QString &imagePath);

    bool isPaused;
    int comboCount;
    int maxScore;

    int orderSerial;

    // UI 控件
    QPushButton *potatoBtn;
    QPushButton *butterBtn;
    QPushButton *milkBtn;
    QPushButton *breadBtn;
    QPushButton *lettuceBtn;
    QPushButton *chickenBtn;
    QPushButton *mixBtn;
    QPushButton *discardBtn;
    QPushButton *submitBtn;
    QPushButton *menuBtn;

    QLabel *bowlLabel;
    QLabel *timerLabel;
    QLabel *scoreLabel;
    QLabel *serialLabel;
    QLabel *orderContentLabel;
    QLabel *feedbackLabel;
    QLabel *maxScoreLabel;

    // 数据
    QStringList currentIngredients;
    QStringList currentOrder;
    int score;
    int completedOrders;
    int timeLeft;
    QTimer *timer;
    int difficulty;

    QStringList extraIngredients;   // 可选食材
    QString getMaxScoreFilePath();  // 根据难度获取最高分文件路径

};

#endif
