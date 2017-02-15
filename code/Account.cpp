#include "Account.hpp"

//getters

const Credentials &Account::getCreds() const {return creds;}
FriendList Account::getFriendList() const {return friendList;}
int Account::getNbOfVictories() const {return nbOfVictories;}
int Account::getNbPnjKilled() const { return nbPnjKilled;}
int Account::getId() const {return id;}

//setters

void Account::setId(int id) {Account::id = id;}
void Account::setPassword(std::string password) {creds.setPassword(password);}
void Account::setUsername(std::string username) {creds.setUsername(username);}
void Account::setNbOfVictories(int nbr) {nbOfVictories = nbr;}
void Account::setNbPnjKilled(int nbr) {nbPnjKilled = nbr;}

