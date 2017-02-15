//
// Created by benjamin on 15/02/17.
//

#include "Command.hpp"

Command::Command(char *data) {
    parse(data);
}

void Command::parse(char *data) {
    int i = extract_action(data);

}

int Command::extract_action(char* data){

    /*
     * Return l'index de début du premier argument de la commande
     */

    int i = 0;
    while (data[i] != ',') {
        action += data[i];
        i++;
    }
    i++;

    return i;
}