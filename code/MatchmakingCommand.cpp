#include "MatchmakingCommand.hpp"

void MatchmakingCommand::parse(char* data) override {
    /*
    * Disons qu'une commande se présente s'envoie dans un string de type : mode,player_id;
    *
    * Ex: si bob veut jouer en classic et que le playerID de bob est 18 -> data = classic,18;
    *
    */
    int i = 0;
    std::string string_player_id;

    // Extracts mode (ex: classic)
    while (data[i] != ',') {
        mode += data[i];
        i++;
    }
    i++; // passe la virgule

    // Extracts the player_id (ex: 18)
    while (data[i] != ';') {
        string_player_id += data[i];
        i++;
    }

    playerConnection.player_id = atoi(string_player_id); // "18" -> 18
}

const PlayerConnection MatchmakingCommand::getPlayerConnection() const {
    return playerConnection;
};

const std::string MatchmakingCommand::getMode() const {
    return mode;
};


