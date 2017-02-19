//
// Created by david on 11/02/17.
//

#include "Database.hpp"

Database::Database(const char* filename) : filename(filename) {
    open();
}

int Database::open() {
    rc = sqlite3_open(filename, &db);

    if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(-1);
    }

    else{
        fprintf(stderr, "Opened database successfully\n");
    }
    return 0;

}

int Database::callback_ranking(void *ptr, int argc, char **argv, char **azColName){
    std::vector<RankingInfos> *list = reinterpret_cast<std::vector<RankingInfos> *>(ptr);
    RankingInfos res;
    res.username = argv[0];
    res.victories= atoi(argv[1]);
    list->push_back(res);
    return 0;
}

int Database::callback_counter(void *count, int argc, char **argv, char **azColName){
    int *c = (int*)count;
    *c = atoi(argv[0]);
    return 0;
}


int Database::callback_account_usrname(void *ptr, int argc, char **argv, char **azColName){
    PublicAccountInfos *infos = reinterpret_cast<PublicAccountInfos*>(ptr);
    infos->username = argv[0];
    infos->victories = atoi(argv[1]);
    infos->pnjKilled = atoi(argv[2]);
    infos->ID = atoi(argv[3]);
    return 0;
}

int Database::callback_account_id(void *ptr, int argc, char **argv, char **azColName){
    std::string *c = (std::string*)ptr;
    *c = argv[0];
    return 0;
}

int Database::callback_FriendList(void *ptr, int argc, char **argv, char **azColName){
    std::vector<std::string> *list = reinterpret_cast<std::vector<std::string>*>(ptr);
    std::string currentFriend = argv[0];
    list->push_back(currentFriend);
    return 0;
}



int Database::insert_account(Credentials credentials) {

    char *zErrMsg = 0;
    int id = get_nb_entries() + 1;

    std::stringstream strm;

    //Je sais pas pq CLion souligne ça en rouge...Ca marche :|

    strm << "insert into Accounts(id,username,password) values(" << id
         << ",'" << credentials.getUsername() << "','" << credentials.getPassword() << "')";


    std::string s = strm.str();
    char *str = &s[0];
    char *query = str;

    rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }

    else{
        fprintf(stdout, "Records created successfully\n");
    }



    return 0;
}

int Database::get_nb_entries() {

    /*Utilisé pour obtenir le prochain id disponible lors du rajout d'un compte dans la database*/

    char *zErrMsg = 0;
    char *query = (char *)"select Count(*) from Accounts";
    int count = 1;

    rc = sqlite3_exec(db, query, callback_counter, &count, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }

    return count;

}

bool Database::is_identifiers_valid(Credentials credentials) {

    char *zErrMsg = 0;
    int count = 0;
    bool valid = false;
    std::stringstream strm;

    strm << "select COUNT(username) FROM Accounts WHERE username='" << credentials.getUsername() << "' AND password='" << credentials.getPassword() << "'";

    std::string s = strm.str();
    char *str = &s[0];
    char *query = str;

    rc = sqlite3_exec(db, query, callback_counter, &count, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }

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
    char *query = (char *)"select username, victories from Accounts order by victories DESC";

    rc = sqlite3_exec(db, query, callback_ranking, &list, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }


    return list;

}

PublicAccountInfos Database::getUsrInfosByUsrname(std::string username) {
    PublicAccountInfos infos;
    char *zErrMsg = 0;
    std::stringstream strm;
    strm << "select username, victories, pnjKilled, id from Accounts WHERE username='" << username << "'";

    std::string s = strm.str();
    char *str = &s[0];
    char *query = str;

    rc = sqlite3_exec(db, query, callback_account_usrname, &infos, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    return infos;
}
int Database::getIDbyUsername(std::string username) {
    return getUsrInfosByUsrname(username).ID;
}

std::string Database::getInfosById(int id) {
    std::string infos;
    char *zErrMsg = 0;
    std::stringstream strm;

    strm << "select username from Accounts WHERE id='" << id << "'";

    std::string s = strm.str();
    char *str = &s[0];
    char *query = str;

    rc = sqlite3_exec(db, query, callback_account_id, &infos, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    return infos;
}

int Database::sendFriendRequest(std::string username, std::string toAdd) {
    // Request for friendship is sent, friendrequests and pendingInvitations are updated accordingly

    char *zErrMsg = 0;
    std::stringstream strm;

    strm << "insert into FriendRequests(ReceiverID, SenderID) values('" << toAdd << "','" << username << "') ;"
         << "insert into PendingInvitations(RequesterID, ReceiverID) values('" << username << "','" << toAdd << "') ;";


    std::string s = strm.str();
    char *str = &s[0];
    char *query = str;

    rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }
    else{
        fprintf(stdout, "Invitation Sent\n");
    }
    return 0;
}



int Database::acceptFriendRequest(std::string username, std::string toAccept) {
    // The user who got the request accepts it and he is added to the requester friend's list and vice versa
    // Friendrequests && pendingInvitations are accordingly updated too
    int id1 = getUsrInfosByUsrname(username).ID;
    int id2 = getUsrInfosByUsrname(toAccept).ID;

    char *zErrMsg = 0;
    std::stringstream strm;

    strm << "insert into FriendList(ID1, ID2) values('" << username << "','" << toAccept << "') ;"
         << "DELETE FROM `FriendRequests` WHERE `ReceiverID`='"<<username<<"' AND `SenderID`='"<<toAccept<<"' ;"
         << "DELETE FROM `PendingInvitations` WHERE `RequesterID`='"<<toAccept<<"' AND `ReceiverID`='"<<username<<"' ;";


    std::string s = strm.str();

    char *str = &s[0];
    char *query = str;

    rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }else{
        fprintf(stdout, "Friend request accepted\n");
    }
    return 0;
}

int Database::removeFriend(std::string username, std::string toRemove){

    char *zErrMsg = 0;
    std::stringstream strm;
    strm<< "DELETE FROM `FriendList` WHERE `ID1`='"<<username<<"' AND `ID2`='"<<toRemove<<"' ;"
        << "DELETE FROM `FriendList` WHERE `ID1`='"<<toRemove<<"' AND `ID2`='"<<username<<"' ;";

    std::string s = strm.str();

    char *str = &s[0];
    char *query = str;

    rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }else{
        fprintf(stdout, "Friend successfully removed, i'm sorry it had to end this way : ( . \n");
    }
    return 0;
}

int Database::declineFriendRequest(std::string username, std::string toDecline) {
    // The user who got the request accepts it and he is added to the requester friend's list and vice versa
    // Friendrequests && pendingInvitations are accordingly updated too
    int id1 = getUsrInfosByUsrname(username).ID;
    int id2 = getUsrInfosByUsrname(toDecline).ID;

    char *zErrMsg = 0;
    std::stringstream strm;

    strm << "DELETE FROM `FriendRequests` WHERE `ReceiverID`='"<<username<<"' AND `SenderID`='"<<toDecline<<"' ;"
         << "DELETE FROM `PendingInvitations` WHERE `RequesterID`='"<<toDecline<<"' AND `ReceiverID`='"<<username<<"' ;";



    std::string s = strm.str();

    char *str = &s[0];
    char *query = str;

    rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }else{
        fprintf(stdout, "Friend request declined\n");
    }
    return 0;
}

std::vector<std::string> Database::getFriendList(int id){
    std::vector<std::string> friendList;
    std::string username = getInfosById(id);
    char *zErrMsg = 0;
    std::stringstream strm;

    strm << "select ID2 from FriendList WHERE ID1 ='"<<username<<"';"
         << "select ID1 from FriendList WHERE ID2 ='"<<username<<"';";
    std::string s = strm.str();

    char *str = &s[0];
    char *query = str;

    rc = sqlite3_exec(db, query, callback_FriendList, &friendList, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    return friendList;
}

std::vector<std::string> Database::getFriendRequests(int id){
    std::vector<std::string> friendRequests;
    std::string username = getInfosById(id);
    char *zErrMsg = 0;
    std::stringstream strm;

    strm << "select SenderID from FriendRequests WHERE ReceiverID ='"<<username<<"'";
    std::string s = strm.str();

    char *str = &s[0];
    char *query = str;

    rc = sqlite3_exec(db, query, callback_FriendList, &friendRequests, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    return friendRequests;
}


Database::~Database() {
    sqlite3_close(db);
}
