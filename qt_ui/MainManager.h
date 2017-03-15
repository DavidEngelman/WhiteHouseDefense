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

private:
    void setTheme(int themeInt);
    QLineEdit *usernameLineEdit;
        QPushButton *searchButton;

        QLabel *userNameLabel;
        QLabel *victoriesLabel;
        QLabel *NPCKilledLabel;


        QString* usernameT;
        QString* victoriesT;
        QString* NPCKilledT;
};

#endif // MAINMANAGER_H
