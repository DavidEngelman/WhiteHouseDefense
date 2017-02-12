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
            char message_buffer[BUFFER_SIZE];
            Command command;
            Credentials * credentials = &command.credentials;

            //Get the the username and password from client
            receive_message(newClient, (char *) message_buffer);

            //Process the username and password
            parse_command((char *) message_buffer, &command);

            if (command.action == "login"){
                handle_login(credentials->username, credentials->password);
            } else if (command.action == "register") {
                handle_register(credentials->username, credentials->password);
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

bool AccountServer::insert_account_in_db(std::string& username, std::string& password) {

    if (myDatabase.insert_account(username, password) == -1) {
        perror("Account creation");
        // TODO: complete
    } else {
        // TODO: complete
    }

    // TODO: modifier ceci pour que ça renvoie True si ça c'est bien passé, False sinon
    return false;
}

bool AccountServer::attemptCreateAccount(std::string& username, std::string& password) {
    return insert_account_in_db(username, password);
}

void AccountServer::handle_register(std::string &username, std::string &password) {
    if (attemptCreateAccount(username, password)) {
        // TODO: Faudra dire au client que ca a marché
    } else {
        // TODO: Faudra dire au client que y a un problème (ex: le username est deja utilisé)
    }
}



//Partie Login

bool AccountServer::checkCredentials(const std::string& username, const std::string& password) {
    // TODO: Check database
    return false;
}

void AccountServer::handle_login(std::string &username, std::string &password) {
    if (checkCredentials(username, password)){
        // Send success message
    } else {
        // Send error message
    }
}




