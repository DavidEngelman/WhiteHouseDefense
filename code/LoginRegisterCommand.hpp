#ifndef PROJET_LOGINREGISTERCOMMAND_HPP
#define PROJET_LOGINREGISTERCOMMAND_HPP

#include "Command.hpp"
#include "Credentials.h"

class LoginRegisterCommand : Command{

private:

    Credentials creds;

public:

    LoginRegisterCommand(char* data);

    void parse(char* data) override ;

    ~LoginRegisterCommand() = default;

};


#endif //PROJET_LOGINREGISTERCOMMAND_HPP
