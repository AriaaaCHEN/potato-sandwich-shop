#ifndef INTROWINDOW_H
#define INTROWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class IntroWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit IntroWindow(QWidget *parent = nullptr);
    ~IntroWindow();

private slots:
    void onCloseClicked();

private:
    QLabel *titleLabel;
    QLabel *textLabel;
    QPushButton *closeBtn;
};

#endif
