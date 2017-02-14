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
            char message_buffer[BUFFER_SIZE];
            get_and_process_command(newClient, message_buffer);
        }
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

bool AccountServer::handle_register(Credentials credentials, int client_sock_fd) {
    bool success = false;

    if (attemptCreateAccount(credentials)) {
        //Success
        send_success(client_sock_fd);
        success = true;
    } else {
        //Error
        send_error(client_sock_fd);
    }
    return success;
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

bool AccountServer::handle_login(Credentials credentials, int client_sock_fd) {
    bool success = false;

    if (checkCredentials(credentials)){
        send_success(client_sock_fd);
        success = true;

    }
    else {
        send_error(client_sock_fd);
    }
    return success;
}

void AccountServer::get_and_process_command(int client, char* message_buffer){
    Command command;
    bool ok = false;

    while (!ok){
        receive_message(client, message_buffer);
        parse_command(message_buffer, &command);

        Credentials credentials = command.credentials;
        std::cout << command.action << std::endl;
        if (command.action == "login"){
            ok = handle_login(credentials, client);
        }
        else if (command.action == "register") {
            ok = handle_register(credentials, client);
        }
        else {
            // Show "unknown command" error
        }

        //On re-init la commande
        command.action ="";
        command.credentials.setUsername("");
        command.credentials.setPassword("");

    }
}






