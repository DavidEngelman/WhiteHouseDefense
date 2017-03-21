#ifndef PROJET_REGISTERUI_HPP
#define PROJET_REGISTERUI_HPP

#include <iostream>
#include <string>
#include "../Abstract/AbstractUI.hpp"
#include "RegisterUI.hpp"
#include "../Abstract/AbstractConsoleUI.hpp"

class RegisterConsoleUI : public RegisterUI, public AbstractConsoleUI {

private:
    void ask_username();

    void ask_password();

public:
    RegisterConsoleUI(RegisterManager *manager);

    void display() override;

    void displaySuccess() override;

    void displayError() override;

    void displayConfirmError() override;
};

#endif // PROJET_REGISTERUI_HPP