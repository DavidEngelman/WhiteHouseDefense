#ifndef PROJET_REGISTER_HPP
#define PROJET_REGISTER_HPP

#include "RegisterManager.hpp"
#include <string>
#include "../Abstract/AbstractUI.hpp"

class RegisterManager;

class RegisterUI : public virtual AbstractUI {

protected:
    RegisterManager *manager;
    std::string username;
    std::string password;
    std::string confirm;

public:
    RegisterUI(RegisterManager *manager) : manager(manager) {};
    virtual ~RegisterUI() = default;

    virtual std::string getUsername() { return username; };
    virtual std::string getPassword() { return password; };
    virtual std::string getConfirm() { return confirm; };

    virtual void display() = 0;
    virtual void displayError() = 0;
    virtual void displayConfirmError() = 0;
};

#endif //PROJET_REGISTER_HPP
