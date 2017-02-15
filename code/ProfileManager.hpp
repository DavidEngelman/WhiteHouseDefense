#ifndef PROFILEMANAGER_HPP
#define PROFILEMANAGER_HPP

#include <string>
#include "ProfileUI.hpp"

class ProfileManager {

private:
	ProfileUI profileUI;

public:
	void getInfo(std::string username);
};

#endif
