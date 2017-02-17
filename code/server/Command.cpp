#include "Command.hpp"

std::string Command::getAction() const {
    return action;
}

void Command::parse(char *data) {
    int i = extract_action(data);

}

int Command::extract_action(char* data){

    /*
     * Return l'index de début du premier argument de la commande
     */

    int i = 0;
    std::string temp_action;

    while ((data[i] != ',') && (data[i] != ';')) { // comme ça une commande peut etre juste par ex: "ranking;"
        temp_action += data[i];                        // au lieu de "ranking," c'est un peu plus clean
        i++;
    }
    i++;

    action = temp_action;
    return i;
}