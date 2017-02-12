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
            Credentials credentials;

            //Get the the username and password from client
            receive_message(newClient, (char *) username_password);

            //Process the username and password
            get_username_and_password((char *) username_password, &credentials);

            attemptCreateAccount(credentials.username, credentials.password);
        }

        //TODO: Finir ça



    }
}

void AccountServer::get_username_and_password(char *data, Credentials *credentials) {
    /*
     *
     * Le format de data doit être "username,password;"

     * Remplis le struct Credentials avec les données dans data
     */
    int i = 0;
    char currentChar = data[0];

    //extracting username
    while (currentChar != ',') {
        credentials->username += currentChar;
        currentChar = data[i + 1];

        i++;
    }

    currentChar = data[i + 1]; // passe la virgule
    i++;

    //extracting password
    while (currentChar != ';') {
        credentials->password += currentChar;
        currentChar = data[i + 1];

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