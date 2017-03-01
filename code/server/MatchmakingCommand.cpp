#include "MatchmakingCommand.hpp"

void MatchmakingCommand::parse(char* data)  {
    /*
    * Disons qu'une commande se présente s'envoie dans un string de type : mode,id;
    *
    * Ex: si bob veut jouer en classic et que le playerID de bob est 18 -> data = classic,18;
    *
    */
    int i = 0;
    std::string string_player_id, string_username;

    // Extracts mode (ex: classic)
    while (data[i] != ',') {
        mode += data[i];
        i++;
    }
    i++; // passe la virgule

    // Extracts the player_id (ex: 18)
    while (data[i] != ',') {
        string_player_id += data[i];
        i++;
    }
    i++;
    int int_player_id = atoi(string_player_id.c_str());
    playerConnection.setPlayer_id(int_player_id); // "18" -> 18

    while (data[i] != ';') {
        string_username += data[i];
        i++;
    }

    playerConnection.setUsername(string_username);

}

const PlayerConnection MatchmakingCommand::getPlayerConnection() const {
    return playerConnection;
};

const std::string MatchmakingCommand::getMode() const {
    return mode;
};


