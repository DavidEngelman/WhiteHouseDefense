//
//

#ifndef PROJET_SETTINGSGUI_HPP
#define PROJET_SETTINGSGUI_HPP


#include "../Abstract/AbstractGUI.hpp"
#include "SettingsUI.hpp"

class SettingsGUI : public AbstractGUI, public SettingsUI {
Q_OBJECT

private:

public:
    SettingsGUI(SettingsManager *manager, QWidget* _parent);

};


#endif //PROJET_SETTINGSGUI_HPP
