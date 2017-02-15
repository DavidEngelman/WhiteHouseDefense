#ifndef PROJET_LOGINREGISTERCOMMAND_HPP
#define PROJET_LOGINREGISTERCOMMAND_HPP

#include "Command.hpp"
#include "Credentials.h"

class LoginRegisterCommand : public Command{

private:

    Credentials creds;

public:

    LoginRegisterCommand() = default;

    void parse(char* data) override ;

    ~LoginRegisterCommand() = default;

    const Credentials &getCreds() const;

};


#endif //PROJET_LOGINREGISTERCOMMAND_HPP
