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
    infos->friendList = argv[3];
    infos->friendRequests = argv[4];
    infos->pendingInvitation = argv[5];
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
    char *query = "select Count(*) from Accounts";
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
    char *query = "select username, victories from Accounts order by victories DESC";

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
    strm << "select username, victories, pnjKilled, friendList, friendRequests, pendingInvitation from Accounts WHERE username='" << username << "'";

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

int Database::sendFriendRequest(std::string username, std::string toAdd) {
    // Request for friendship is sent, friendrequests and pendingInvitations are updated accordingly

    std::string currentPendingInvit = addToString(getUsrInfosByUsrname(username).pendingInvitation,toAdd);
    std::string currentFriendRequests = addToString(getUsrInfosByUsrname(toAdd).friendRequests, username);

    char *zErrMsg = 0;
    std::stringstream strm;
    strm << "UPDATE Accounts SET pendingInvitation='"<<currentPendingInvit<< "' WHERE username='"<<username<< "';"
         << "UPDATE Accounts SET friendRequests='"<<currentFriendRequests<< "' WHERE username='"<<toAdd<< "'" ;

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
    std::string currentFriendList = addToString(getUsrInfosByUsrname(username).friendList, toAccept);
    std::string currentFriendList2 = addToString(getUsrInfosByUsrname(toAccept).friendList,username);
    std::string currentFriendRequests = removeFromString(getUsrInfosByUsrname(username).friendRequests, toAccept);
    std::string currentPendingInvit = removeFromString(getUsrInfosByUsrname(toAccept).friendList,username);

    char *zErrMsg = 0;
    std::stringstream strm;
    strm << "UPDATE Accounts SET friendList='"<<currentFriendList<< "' WHERE username='"<<username<< "';"
         << "UPDATE Accounts SET friendList='"<<currentFriendList2<< "' WHERE username='"<<toAccept<< "';"
         << "UPDATE Accounts SET friendRequests='"<<currentFriendRequests<< "' WHERE username='"<<username<< "';"
         << "UPDATE Accounts SET pendingInvitation='"<<currentPendingInvit<< "' WHERE username='"<<toAccept<< "'";

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

std::string Database::addToString(std::string original, std::string toAdd){
    if(original.size()== 0 ){
        original = toAdd;
    }else{
        original = original + "," + toAdd;
    }
    return original;
}

std::string Database::removeFromString(std::string original, std::string toRemove){
    std::string newString = "";
    int index = 0 ;

    while( index < original.size() ){
        std::string tempstring = "";
        while (original[index] != ',' && index < original.size() ){
            tempstring += original[index];
            index++;
        }
        if (tempstring != toRemove){
            newString += tempstring;
        }
        index++;
    }
    return newString;
}

Database::~Database() {
    sqlite3_close(db);
}
