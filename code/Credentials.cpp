#include "Credentials.h"

Credentials::Credentials(): username("\0"), password("\0"){}

Credentials::Credentials(const std::string& usr, const std::string& pswrd): username(usr), password(pswrd) {}

std::string Credentials::getUsername() const { return username;}

std::string Credentials::getPassword() const { return password;}

void Credentials::setUsername(const std::string &newUserName) {username = newUserName;}

void Credentials::setPassword(const std::string &newPassword) {password = newPassword;}
