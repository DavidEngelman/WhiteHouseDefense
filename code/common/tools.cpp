#include "tools.hpp"

std::string bool_to_string(bool _bool){
    return _bool ? "true" : "false";
}

bool stringToBool(const std::string& str) {
    return str == "true";
}