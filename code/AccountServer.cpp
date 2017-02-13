//
// Created by benjamin on 11/02/17.
//

#include "AccountServer.hpp"


AccountServer::AccountServer(int port, const char *databaseName) : Server(port), myDatabase(Database(databaseName)) {}

void AccountServer::run() {
    start_socket_listen();

    int newClient;

    while (1) {
        newClient = accept_connection();
        std::cout << "New client connected wouhouuu" << std::endl;
        //add_new_client(newClient); Je laisse ca la au cas ou

        if (!fork()) {
            //TODO: Rajouter une boucle pour que si le client se rate une fois il puisse rééssayer
            char message_buffer[BUFFER_SIZE];
            Command command;
            Credentials credentials;

            //Get the the username and password from client
            receive_message(newClient, (char *) message_buffer);

            //Process the username and password
            parse_command((char *) message_buffer, &command);
            credentials = command.credentials;

            if (command.action == "login"){
                handle_login(credentials, newClient);
            }
            else if (command.action == "register") {
                handle_register(credentials, newClient);
            }
            else {
                // Show "unknown command" error
            }
        }

        //TODO: Finir ça
    }
}

void AccountServer::parse_command(char *data, Command *command) {
    /* Parses a string formatted into "command,username,password;" into a
     * Command object.
     *
     * Example: "login,bob,leponge" -> Command{"command", Credentials{"bob", "leponge"}}
     */

    // TODO? Gerer les cas où le message n'est pas correct (genre "login,bob;")

    std::string username;
    std::string password;
    int i = 0;

    // Extracts action string (ex: login)
    while (data[i] != ',') {
        command->action += data[i];
        i++;
    }
    i++; // passe la virgule

    // Extracts the username (ex: bob)
    while (data[i] != ',') {

        username += data[i];
        i++;
    }
    i++; // passe la virgule

    // Extracts the password (ex: leponge)
    while (data[i] != ';') {
        password += data[i];
        i++;
    }

    command->credentials.setUsername(username);
    command->credentials.setPassword(password);

}

//Partie Register

bool AccountServer::insert_account_in_db(Credentials credentials) {
    //Return True si ca c'est bien passé, false sinon

    return myDatabase.insert_account(credentials) != -1;
}

bool AccountServer::attemptCreateAccount(Credentials credentials) {
    return insert_account_in_db(credentials);
}

void AccountServer::handle_register(Credentials credentials, int client_sock_fd) {
    if (attemptCreateAccount(credentials)) {
        //Success
        send_success(client_sock_fd);
    } else {
        //Error
        send_error(client_sock_fd);
    }
}

void AccountServer::send_error(int client_sock_fd){
    send_message(client_sock_fd, "-1");

}

void AccountServer::send_success(int client_sock_fd){
    send_message(client_sock_fd, "1");
}

//Partie Login

bool AccountServer::checkCredentials(Credentials credentials) {
    return  myDatabase.is_identifiers_valid(credentials);
}

void AccountServer::handle_login(Credentials credentials, int client_sock_fd) {
    if (checkCredentials(credentials)){
        send_success(client_sock_fd);
    } else {
        send_error(client_sock_fd);
    }
}






