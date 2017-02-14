#ifndef PROFILMANAGER_HPP
#define PROFILMANAGER_HPP

#include <string>
#include "ProfilUI.hpp"

class ProfilManager {

private:
	ProfilUI profilUI;

public:
	void getInfo(std::string username);
};

#endif
