#ifndef PROJET_ICONSELECTIONWIDGET_HPP
#define PROJET_ICONSELECTIONWIDGET_HPP


#include <QtWidgets/QWidget>
#include "SettingsGUI.hpp"

class IconSelectionWidget : public QWidget{
    Q_OBJECT

private:

    SettingsGUI* parentS;

public:

    IconSelectionWidget(SettingsGUI* _parent);

public slots:

    void handleIconChoice(int choice);
};


#endif //PROJET_ICONSELECTIONWIDGET_HPP
