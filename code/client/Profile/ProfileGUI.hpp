#ifndef PROJET_PROFILEGUI_HPP
#define PROJET_PROFILEGUI_HPP

#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include "../Abstract/AbstractGUI.hpp"
#include "ProfileManager.hpp"
#include "ProfileUI.hpp"

class ProfileGUI : public AbstractGUI, public ProfileUI {
Q_OBJECT

private:
    QLineEdit *usernameL;
    QPushButton *searchButton;
    //ProfileManager *manager;
    QString* usernameT;
    QString* victoriesT;
    QString* pnjKilledT;

public slots:
    void showUser();

public:
    ProfileGUI(ProfileManager *manager);
    virtual ~ProfileGUI();
    void display() override;

    void displayNoSuchProfileError() override;

    void updateProfile() override;
};


#endif //PROJET_PROFILEGUI_HPP
