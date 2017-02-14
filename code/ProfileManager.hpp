#ifndef PROFILMANAGER_HPP
#define PROFILMANAGER_HPP

#include <string>
#include "ProfilUI.hpp"

class ProfileManager {

private:
	ProfileUI profileUI;

public:
	void getInfo(std::string username);
};

#endif
