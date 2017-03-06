#include "MainManager.h"
#include "Loginmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainManager w;
    w.show();

    return a.exec();
}
