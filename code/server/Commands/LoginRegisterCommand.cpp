#include "LoginRegisterCommand.hpp"

void LoginRegisterCommand::parse(char *data) {
    /* Parses a string formatted into "command,username,password;" into a
     * Command object.
     *
     * Example: "login,bob,leponge" -> Command{"command", Credentials{"bob", "leponge"}}
     */
    Command::parse(data); // Fait parse de l'action
    creds.setUsername(getNextToken());
    creds.setPassword(getNextToken());
}

const Credentials &LoginRegisterCommand::getCreds() const {
    return creds;
}
