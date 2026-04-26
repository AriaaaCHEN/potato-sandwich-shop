#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

signals:
    void continueGame();    // 继续游戏
    void restartGame();     // 重新开始
    void backToLobby();     // 返回大厅

private slots:
    void onContinueClicked();
    void onRestartClicked();
    void onBackClicked();

private:
    QPushButton *continueBtn;
    QPushButton *restartBtn;
    QPushButton *backBtn;
};

#endif
