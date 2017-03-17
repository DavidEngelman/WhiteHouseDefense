//
// Created by titi on 12/03/17.
//

#ifndef PROJET_QCUSTOMBUTTON_H
#define PROJET_QCUSTOMBUTTON_H


#include <QtWidgets/QPushButton>

class QCustomButton : public QPushButton {
    Q_OBJECT

private:
    int myNumber;

private slots:

    void clickedInt();

signals:

    void clicked(int number);

public:
    QCustomButton(int number, QString text, QWidget *parent);
};


#endif //PROJET_QCUSTOMBUTTON_H
