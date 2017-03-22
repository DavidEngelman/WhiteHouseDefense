#ifndef PROJET_REGISTERGUI_HPP
#define PROJET_REGISTERGUI_HPP


#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "../Abstract/AbstractGUI.hpp"
#include "RegisterUI.hpp"

class RegisterGUI : public AbstractGUI, public RegisterUI {
    Q_OBJECT

public slots:
    void registerUser();
    void cancelRegister();

private:
    QLineEdit *usernameL;
    QLineEdit *passwordL;
    QLineEdit *confirmL;
    QPushButton *connect;
    QPushButton *cancel;

public:
    RegisterGUI(RegisterManager *manager, QWidget *_parent);

    virtual ~RegisterGUI();

    void display() override;

    void displaySuccess();

    void displayError() override;

    void displayConfirmError() override;
};


#endif //PROJET_REGISTERGUI_HPP
