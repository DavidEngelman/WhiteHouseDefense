#include "Server.hpp"
#include "AccountServer.hpp"


int main() {
    std::cout << "Hello, World!" << std::endl;

    AccountServer myTestServer = AccountServer(5555, "database.db");

    myTestServer.run();

    return 0;
}
