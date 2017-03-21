#ifndef PROJET_ICONWIDGET_HPP
#define PROJET_ICONWIDGET_HPP


#include <QtWidgets/QLabel>

class IconLabel : public QLabel{

private:

    int id;
    QLabel* label;

public:
    IconLabel(int _id, QString path_to_image);
    ~IconLabel();
    void clickedInt();

signals:

    void clicked(int number);

};


#endif //PROJET_ICONWIDGET_HPP
