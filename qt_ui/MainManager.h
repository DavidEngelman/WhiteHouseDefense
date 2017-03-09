#ifndef MAINMANAGER_H
#define MAINMANAGER_H

#include <QWidget>
#include <QMainWindow>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>
#include <QFile>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QFrame>
#include <QtMultimedia/QMediaPlayer>
#include <iostream>
#include <QGraphicsEffect>
#include "Loginmanager.h"

class MainManager : public QWidget
{
    Q_OBJECT

public:

    explicit MainManager(QWidget *parent = 0);
    ~MainManager();

public slots:
    void openWindow();


private:
    void setTheme(int themeInt);
    QPushButton *loginButton;
    QPushButton *registerButton;
    QPushButton *quitButton;
};

#endif // MAINMANAGER_H
