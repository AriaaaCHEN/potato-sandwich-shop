#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartClicked();
    void onIntroClicked();
    void onExitClicked();

private:
    QLabel *bgLabel;
    QPushButton *startBtn;
    QPushButton *introBtn;
    QPushButton *exitBtn;
};

#endif
