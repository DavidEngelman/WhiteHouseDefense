#ifndef PROJET_TOOLS_HPP
#define PROJET_TOOLS_HPP

#include <string>

std::string bool_to_string(bool my_bool);
bool stringToBool(const std::string& str);
std::string cryptPassword(std::string password);
std::string bool_to_winner_loser(bool _bool);
std::string bool_to_victory_defeat(bool _bool);


#endif //PROJET_TOOLS_HPP
