#ifndef DIFFICULTYWINDOW_H
#define DIFFICULTYWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class DifficultyWindow : public QMainWindow
{
    Q_OBJECT

public:
    DifficultyWindow(QWidget *parent = nullptr);
    ~DifficultyWindow();

private slots:
    void onSimpleClicked();
    void onNormalClicked();
    void onHardClicked();

private:
    QPushButton *simpleBtn;
    QPushButton *normalBtn;
    QPushButton *hardBtn;
};

#endif
