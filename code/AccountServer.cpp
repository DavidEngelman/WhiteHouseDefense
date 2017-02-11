//
// Created by benjamin on 11/02/17.
//

#include "AccountServer.hpp"

AccountServer::AccountServer(int port, const char* databaseName): Server(port), myDatabase(Database(databaseName)){}

void AccountServer::run(){

    int newClient;

    while (1){
        newClient = accept_connection();
        //add_new_client(newClient); Je laisse ca la au cas ou

        if ( !fork() ){

            char* username_password[500]; //Je met 500 par défaut pour l'instant;
            std::vector<std::string> username_password_vect;

            //Get the the username and password from client
            receive_message(newClient, username_password);

            //Process the username and password
            username_password_vect = get_username_and_password(username_password); // TODO: check pq ça marche pas

            //Account creation
            attemptCreateAccount(username_password[0], username_password[1]);


        }

        //TODO: Finir ça



    }
}

std::vector<std::string> AccountServer::get_username_and_password (char* data){

    /*
     *
     * Le format de data doit être "username,password;"

     * Return un tableau de deux composante:
     * la première : le username
     * la deuxième : le password

     * */

    std::vector<std::string> username_password(2);


    int i = 0;
    char currentChar = data[0];

    while (currentChar != ','){

        //extracting username
        username_password[0] += currentChar;
        currentChar = data[i+1];

        i++;

    }

    currentChar = data[i+1]; // passe la virgule
    i++;

    while (currentChar != ';'){

        //extracting password
        username_password[1] += currentChar;
        currentChar = data[i+1];

        i++;

    }

    return username_password;
}

//Partie Register

void AccountServer::insert_account_in_db(std::string username, std::string password){

    if (myDatabase.insert_account(username, password) == -1 ){
        perror("Account creation");
        //TODO: Faudra dire au client que y a un problème (ex: le username est deja utilisé)
    }
    else{
        //TODO: Faudra dire au client que ca a marché
    }
}

void AccountServer::attemptCreateAccount(std::string username, std::string password) {

    insert_account_in_db (username, password);
}

//Partie Login

void AccountServer::checkCredentials(std::string username, std::string password) {}