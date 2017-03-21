#ifndef PROJET_ICONWIDGET_HPP
#define PROJET_ICONWIDGET_HPP


#include <QtWidgets/QLabel>
#include "Settings/IconSelectionWidget.hpp"

class IconLabel : public QLabel{

Q_OBJECT

private:
    int id;
    QLabel* label;

public:
    IconLabel(int _id, QString path_to_image, IconSelectionWidget* parentS);
    ~IconLabel();

private slots:
    void clickedInt();

public: signals:
    void clicked();
    void clicked(int);

protected:
    void mousePressEvent(QMouseEvent* event);

};


#endif //PROJET_ICONWIDGET_HPP
