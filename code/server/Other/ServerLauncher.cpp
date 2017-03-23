#include "Server.hpp"
#include "../Account/AccountServer.hpp"
#include "../Game/MatchMaker.hpp"


void * launch_account_server(void * dummy){
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

    pthread_t server_threads[2];

    pthread_create(&server_threads[0], NULL, &launch_account_server, NULL);
    pthread_create(&server_threads[1], NULL, &launch_matchmaking_server, NULL);

    for (int i=0; i<2; i++){
        pthread_join(server_threads[i],NULL);
    }


    return 0;
}
