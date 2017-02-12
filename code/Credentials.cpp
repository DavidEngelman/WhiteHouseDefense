//
// Created by benjamin on 12/02/17.
//

#include "Credentials.h"

Credentials::Credentials(): username("\0"), password("\0"){}

Credentials::Credentials(const std::string& usr, const std::string& pswrd): username(usr), password(pswrd) {}

std::string Credentials::getUsername() { return username;}

std::string Credentials::getPassword() { return password;}

void Credentials::setUsername(const std::string &newUserName) {username = newUserName;}

void Credentials::setPassword(const std::string &newPassword) {password = newPassword;}
