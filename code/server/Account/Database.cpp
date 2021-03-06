#include "Database.hpp"

Database::Database(const char *filename) : filename(filename) {
    open();
}

int Database::open() {

    rc = sqlite3_open(filename, &db);


    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (-1);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }
    return 0;

}

int Database::exec(const char *query, int (*callback)(void *, int, char **, char **), void *data, char *ErrMsg) {


    rc = sqlite3_exec(db, query, callback, data, &ErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", ErrMsg);
        sqlite3_free(ErrMsg);
        return -1;
    }
    return 0;
}

int Database::callback_ranking(void *ptr, int argc, char **argv, char **azColName) {
    std::vector<RankingInfos> *list = reinterpret_cast<std::vector<RankingInfos> *>(ptr);
    RankingInfos res;
    res.username = argv[0];
    res.victories = atoi(argv[1]);
    list->push_back(res);
    return 0;
}

int Database::callback_counter(void *count, int argc, char **argv, char **azColName) {
    int *c = (int *) count;
    *c = atoi(argv[0]);
    return 0;
}


int Database::callback_account_usrname(void *ptr, int argc, char **argv, char **azColName) {
    PublicAccountInfos *infos = reinterpret_cast<PublicAccountInfos *>(ptr);
    infos->username = argv[0];
    infos->victories = argv[1];
    infos->defeats = argv[2];
    infos->pnjKilled = argv[3];
    infos->ID = atoi(argv[4]);
    infos->iconID =argv[5];
    return 0;
}

int Database::callback_username(void *ptr, int argc, char **argv, char **azColName) {
    std::string *c = (std::string *) ptr;
    *c = argv[0];
    return 0;
}



int Database::callback_FriendList(void *ptr, int argc, char **argv, char **azColName) {
    std::vector<std::string> *list = reinterpret_cast<std::vector<std::string> *>(ptr);
    std::string currentFriend = argv[0];
    list->push_back(currentFriend);
    return 0;
}
int Database::callback_FriendRequests(void *ptr, int argc, char **argv, char **azColName) {
    std::vector<std::string> *list = reinterpret_cast<std::vector<std::string> *>(ptr);
    std::string currentFriend = argv[0];
    list->push_back(currentFriend);
    return 0;
}

int Database::callback_FriendInvitations(void *ptr, int argc, char **argv, char **azColName) {
    std::vector<std::string> *list = reinterpret_cast<std::vector<std::string> *>(ptr);
    std::string currentFriend = argv[0];
    list->push_back(currentFriend);
    return 0;
}



int Database::insert_account(Credentials credentials) {

    char *zErrMsg = 0;
    std::string command = "";
    command += "insert into Accounts(username,password) values('"
               + credentials.getUsername() + "','"
               + credentials.getPassword() + "')";


    char *query = (char *) command.c_str();
    return exec(query, NULL, 0, zErrMsg);

}

int Database::update_username(int id, std::string newUsername) {

    std::string oldUsername = getUsernameByID(id);
    std::cout<<oldUsername;
    char *zErrMsg = 0;

    std::string command = "";

    command += "UPDATE Accounts SET username = '" + newUsername + "' WHERE id = " + std::to_string(id) + ";"
               + "UPDATE FriendList SET USERNAME1 = '" + newUsername + "' WHERE USERNAME1 = '" + oldUsername + "';"
               + "UPDATE FriendList SET USERNAME2 = '" + newUsername + "' WHERE USERNAME2 = '" + oldUsername + "';"
               + "UPDATE FriendRequests SET Receiver = '" + newUsername + "' WHERE Receiver = '" + oldUsername + "';"
               + "UPDATE FriendRequests SET Sender = '" + newUsername + "' WHERE Sender = '" + oldUsername + "';"
               + "UPDATE PendingInvitations SET Requester = '" + newUsername + "' WHERE Requester = '" + oldUsername + "';"
               + "UPDATE PendingInvitations SET Receiver = '" + newUsername + "' WHERE Receiver = '" + oldUsername + "';";

    char *query = (char *) command.c_str();

    return exec(query, NULL, 0, zErrMsg);

}

int Database::update_password(int id, std::string newPassword) {

    char *zErrMsg = 0;

    std::string command = "";
    command += "UPDATE Accounts SET password = '" + newPassword + "' WHERE id = " + std::to_string(id);

    char *query = (char *) command.c_str();

    return exec(query, NULL, 0, zErrMsg);

}

int Database::updateIcon(int id, int newPicture) {

    char *zErrMsg = 0;

    std::string command = "";
    command += "UPDATE Accounts SET profilePicture = '" + std::to_string(newPicture) +
            "' WHERE id = " + std::to_string(id);

    char *query = (char *) command.c_str();

    return exec(query, NULL, 0, zErrMsg);

}

bool Database::is_identifiers_valid(Credentials credentials) {

    char *zErrMsg = 0;
    int count = 0;
    bool valid = false;
    std::string command = "";
    command +=
            "select COUNT(username) FROM Accounts WHERE username='" + credentials.getUsername() + "' AND password='" +
            credentials.getPassword() + "'";

    char *query = (char *) command.c_str();

    exec(query, callback_counter, &count, zErrMsg);


    if (count == 1)
        valid = true;


    return valid;
}

std::vector<RankingInfos> Database::getRanking() {
    /*
     * Renvoi un vector d'element RankingInfos trié par ordre décroissant selon le nombre de victoires.
     * Un élement RankingInfos est composé d'un attribut username et d'un attribut victories
     * Ex: [elem1, elem2, elem3]
     * elem1.username = Bob , elem1.victories = 60 | elem2.username = Bobette , elem2.victories = 21 | ect...
     *
     * */
    std::vector<RankingInfos> list;
    char *zErrMsg = 0;
    char *query = (char *) "select username, victories from Accounts order by victories DESC";

    exec(query, callback_ranking, &list, zErrMsg);

    return list;

}

PublicAccountInfos Database::getUsrInfosByUsrname(std::string username) {
    PublicAccountInfos infos;
    char *zErrMsg = 0;
    std::string command = "";
    command += "select username, victories, defeats, pnjKilled, id, profilePicture from Accounts WHERE username='" + username + "'";

    char *query = (char *) command.c_str();

    exec(query, callback_account_usrname, &infos, zErrMsg);

    return infos;
}

std::string Database::getUsernameByID(int ID) {
    std::string username;
    char *zErrMsg = 0;
    std::string command = "";
    command += "select username from Accounts WHERE id='" + std::to_string(ID) + "'";

    char *query = (char *) command.c_str();

    exec(query, callback_username, &username, zErrMsg);

    return username;
}

int Database::getIDbyUsername(std::string username) {
    return getUsrInfosByUsrname(username).ID;
}

int Database::sendFriendRequest(std::string username, std::string toAdd) {
    // Request for friendship is sent, friendrequests and pendingInvitations are updated accordingly

    char *zErrMsg = 0;
    std::string command = "";
    command += "insert into FriendRequests(Receiver, Sender) values('" + toAdd + "','" + username + "') ;"
               + "insert into PendingInvitations(Requester, Receiver) values('" + username + "','" + toAdd + "') ;";

    char *query = (char *) command.c_str();

    return exec(query, NULL, 0, zErrMsg);

}


int Database::acceptFriendRequest(std::string username, std::string toAccept) {
    // The user who got the request accepts it and he is added to the requester friend's list and vice versa
    // Friendrequests && pendingInvitations are accordingly updated too
    char *zErrMsg = 0;
    std::string command = "";
    command += "insert into FriendList(USERNAME1, USERNAME2) values('" + username + "','" + toAccept + "') ;" +
               "DELETE FROM `FriendRequests` WHERE `Receiver`='" + username + "' AND `Sender`='" + toAccept +
               "' ;" + "DELETE FROM `PendingInvitations` WHERE `Requester`='" + toAccept + "' AND `Receiver`='" +
               username + "' ;";


    char *query = (char *) command.c_str();

    return exec(query, NULL, 0, zErrMsg);
}

int Database::removeFriend(std::string username, std::string toRemove) {

    char *zErrMsg = 0;
    std::string command = "";
    command += "DELETE FROM `FriendList` WHERE `USERNAME1`='" + username + "' AND `USERNAME2`='" + toRemove + "' ;" +
               "DELETE FROM `FriendList` WHERE `USERNAME1`='" + toRemove + "' AND `USERNAME2`='" + username + "' ;";

    char *query = (char *) command.c_str();

    return exec(query, NULL, 0, zErrMsg);
}

int Database::declineFriendRequest(std::string username, std::string toDecline) {
    // The user who got the request accepts it and he is added to the requester friend's list and vice versa
    // Friendrequests && pendingInvitations are accordingly updated too

    char *zErrMsg = 0;
    std::string command = "";
    command += "DELETE FROM `FriendRequests` WHERE `Receiver`='" + username + "' AND `Sender`='" + toDecline +
               "' ;" + "DELETE FROM `PendingInvitations` WHERE `Requester`='" + toDecline + "' AND `Receiver`='" +
               username + "' ;";


    char *query = (char *) command.c_str();

    return exec(query, NULL, 0, zErrMsg);
}

int Database::cancelInvitation(std::string username, std::string toCancel) {
    char *zErrMsg = 0;
    std::string command = "";

    command += "DELETE FROM `FriendRequests` WHERE `Receiver`='" + toCancel + "' AND `Sender`='" + username +
               "' ;" + "DELETE FROM `PendingInvitations` WHERE `Requester`='" + username + "' AND `Receiver`='" +
               toCancel + "' ;";


    char *query = (char *) command.c_str();

    return exec(query, NULL, 0, zErrMsg);
}

std::vector<std::string> Database::getFriendList(std::string username) {
    std::vector<std::string> friendList;
    char *zErrMsg = 0;
    std::string command = "";
    command += "select USERNAME2 from FriendList WHERE USERNAME1 ='" + username + "';" + "select USERNAME1 from FriendList WHERE USERNAME2 ='" +
               username + "';";

    char *query = (char *) command.c_str();

    exec(query, callback_FriendList, &friendList, zErrMsg);
    return friendList;
}

std::vector<std::string> Database::getFriendRequests(std::string username) {
    std::vector<std::string> friendRequests;
    char *zErrMsg = 0;
    std::string command = "";
    command += "select Sender from FriendRequests WHERE Receiver ='" + username + "'";

    char *query = (char *) command.c_str();

    exec(query, callback_FriendRequests, &friendRequests, zErrMsg);

    return friendRequests;
}

std::vector<std::string> Database::getPendingInvitations(std::string username) {
    std::vector<std::string> friendRequests;
    char *zErrMsg = 0;
    std::string command = "";
    command += "select Receiver from PendingInvitations WHERE Requester ='" + username + "'";

    char *query = (char *) command.c_str();

    exec(query, callback_FriendInvitations, &friendRequests, zErrMsg);

    return friendRequests;
}

void Database::updateAfterGameStats(int id, int pnjKilled, bool isWinner) {
    char *zErrMsg = 0;
    std::string command = "";
    int victoryIncrement = 0;
    int defeatIncrement = 1;
    if (isWinner) {
        victoryIncrement = 1;
        defeatIncrement = 0;
    }
    command += "UPDATE Accounts SET pnjKilled = pnjKilled + " + std::to_string(pnjKilled) + ", victories = victories + "
               + std::to_string(victoryIncrement) + ", defeats = defeats + " + std::to_string(defeatIncrement)
               + " WHERE id = " + std::to_string(id) + ";";

    std::cout << "Commande : " << command << std::endl;
    char *query = (char *) command.c_str();

    exec(query, NULL, 0, zErrMsg);
}


Database::~Database() {
    sqlite3_close(db);
}
