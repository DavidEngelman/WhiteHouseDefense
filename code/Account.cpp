#include "Account.hpp"

//getters

std::string Account::getUsername() {return creds.getUsername();}
std::string Account::getPassword() {return creds.getPassword();}
FriendList Account::getFriendList() {return friendList;}
int Account::getNbOfVictories() {return nbOfVictories;}
int Account::getNbPnjKilled() { return nbPnjKilled;}

//setters

void Account::setPassword(std::string password) {creds.setPassword(password);}
void Account::setUsername(std::string username) {creds.setUsername(username);}
void Account::setNbOfVictories(int nbr) {nbOfVictories = nbr;}
void Account::setNbPnjKilled(int nbr) {nbPnjKilled = nbr;}

