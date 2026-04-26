#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartClicked();    // 开始游戏 → 打开难度选择
    void onIntroClicked();    // 游戏简介
    void onExitClicked();     // 退出游戏

private:
    // 按钮
    QPushButton *startBtn;
    QPushButton *introBtn;
    QPushButton *exitBtn;
};

#endif
