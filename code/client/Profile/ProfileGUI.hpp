#ifndef PROJET_PROFILEGUI_HPP
#define PROJET_PROFILEGUI_HPP

#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include "../Abstract/AbstractGUI.hpp"
#include "ProfileManager.hpp"
#include "ProfileUI.hpp"

class ProfileGUI : public AbstractGUI, public ProfileUI {
Q_OBJECT

private:
    QLineEdit *usernameLineEdit;
    QPushButton *searchButton;
    QPushButton *homeButton;

    QLabel *userNameLabel;
    QLabel *victoriesLabel;
    QLabel *NPCKilledLabel;


    QString* usernameT;
    QString* victoriesT;
    QString* NPCKilledT;

public slots:
    void showUser();
    void goToMain();

public:
    ProfileGUI(ProfileManager *manager);

    virtual ~ProfileGUI();

    void display() override;

    void displayNoSuchProfileError() override;

    void updateProfile() override;

};


#endif //PROJET_PROFILEGUI_HPP
