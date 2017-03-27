
#include "SupporterConnection.hpp"

int SupporterConnection::getSupporterSocket() { return supporterSocket; }
void SupporterConnection::setSupporterSocket(int player) { supporterSocket = player; }

std::string SupporterConnection::getPlayerSupported() { return playerSupported; }
void SupporterConnection::setPlayerSupported(std::string &player) { playerSupported = player; }