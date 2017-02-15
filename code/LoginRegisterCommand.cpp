#include "LoginRegisterCommand.hpp"

void LoginRegisterCommand::parse(char *data) {

/* Parses a string formatted into "command,username,password;" into a
 * Command object.
 *
 * Example: "login,bob,leponge" -> Command{"command", Credentials{"bob", "leponge"}}
 */

    // TODO? Gerer les cas où le message n'est pas correct (genre "login,bob;")

    std::string username;
    std::string password;

    int i = extract_action(data);
    std::cout << data[i] << std::endl;

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

    creds.setUsername(username);
    creds.setPassword(password);
}

const Credentials &LoginRegisterCommand::getCreds() const {
    return creds;
}
