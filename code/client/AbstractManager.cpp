
#include <iostream>
#include "AbstractManager.h"

AbstractManager::AbstractManager(char* addr, App* my_app) : server_ip_address(addr), my_master_app(my_app) {
    std::cout << "hqisd" << std::endl;
}
//AbstractManager::~AbstractManager() {}
