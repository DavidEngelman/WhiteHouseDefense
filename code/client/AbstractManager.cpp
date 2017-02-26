
#include <iostream>
#include "AbstractManager.h"

AbstractManager::AbstractManager(char* addr, App* my_app) : server_ip_address(addr), master_app(my_app) {}
AbstractManager::~AbstractManager() {}
