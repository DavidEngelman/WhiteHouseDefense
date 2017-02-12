//
// Created by benjamin on 11/02/17.
//

#include "AccountServer.hpp"


AccountServer::AccountServer(int port, const char *databaseName) : Server(port), myDatabase(Database(databaseName)) {}

void AccountServer::run() {

    int newClient;

    while (1) {
        newClient = accept_connection();
        //add_new_client(newClient); Je laisse ca la au cas ou

        if (!fork()) {
            char username_password[BUFFER_SIZE];
            Command command;
            Credentials * credentials = &command.credentials;

            //Get the the username and password from client
            receive_message(newClient, (char *) username_password);

            //Process the username and password
            parse_command((char *) username_password, &command);

            if (command.action == "login"){
                // Check credentials
            } else if (command.action == "register") {
                attemptCreateAccount(credentials->username, credentials->password);
            } else {
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

    int i = 0;

    // Extracts action string (ex: login)
    while (data[i] != ',') {
        command->action += data[i];
        i++;
    }
    i++; // passe la virgule

    // Extracts the username (ex: bob)
    while (data[i] != ',') {
        (command->credentials).username += data[i];
        i++;
    }
    i++; // passe la virgule

    // Extracts the password (ex: leponge)
    while (data[i] != ';') {
        (command->credentials).password += data[i];
        i++;
    }
}

//Partie Register

void AccountServer::insert_account_in_db(std::string username, std::string password) {

    if (myDatabase.insert_account(username, password) == -1) {
        perror("Account creation");
        //TODO: Faudra dire au client que y a un problème (ex: le username est deja utilisé)
    } else {
        //TODO: Faudra dire au client que ca a marché
    }
}

void AccountServer::attemptCreateAccount(std::string username, std::string password) {
    insert_account_in_db(username, password);
}

//Partie Login

void AccountServer::checkCredentials(std::string username, std::string password) {}


