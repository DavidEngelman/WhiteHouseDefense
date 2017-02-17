#include "Server.hpp"
#include "AccountServer.hpp"
#include "MatchMaker.hpp"


void * launch_account_server(void * bla){
    AccountServer accountServer = AccountServer(5555, "database.db");
    accountServer.run();
    return nullptr;
}

void * launch_matchmaking_server(void * dummy){
    MatchMaker matchMaker = MatchMaker(5556);
    matchMaker.run();
    return nullptr;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    pthread_t account_server_thread;
    pthread_create(&account_server_thread, NULL, &launch_account_server, NULL);

    pthread_t matchmaker_thread;
    pthread_create(&matchmaker_thread, NULL, &launch_matchmaking_server, NULL);

    return 0;
}
