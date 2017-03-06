#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "MainManager.h"

class LoginManager : public QWidget
{
    Q_OBJECT
public:
    explicit LoginManager();

signals:

public slots:
    void loginUser();

private:
    QLineEdit *usernameL;
    QLineEdit *passwordL;
    QPushButton *connect;

};

#endif // LOGINMANAGER_H
