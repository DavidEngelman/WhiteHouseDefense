//
// Created by benjamin on 10/02/17.
// --- Quel egocentrique --- :p
//

#include "Server.hpp"
#include "AccountServer.hpp"


int main() {
    std::cout << "Hello, World!" << std::endl;

    AccountServer myTestServer = AccountServer(5555, "database.db");

    return 0;
}
