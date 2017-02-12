//
// Created by benjamin on 12/02/17.
//

#ifndef PROJET_CREDENTIALS_H
#define PROJET_CREDENTIALS_H

#include <iostream>
#include <string>

class Credentials {

private:

    std::string username;
    std::string password;

public:

    Credentials();
    Credentials(const std::string& usr, const std::string& pswrd);

    std::string getUsername();
    std::string getPassword();

    void setUsername(const std::string& newUserName);
    void setPassword(const std::string& newPassword);

    virtual ~Credentials() = default;
};


#endif //PROJET_CREDENTIALS_H
