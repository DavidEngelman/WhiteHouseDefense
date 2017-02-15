//
// Created by david on 11/02/17.
//

#ifndef PROJET_DATABASE_H
#define PROJET_DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include <string.h>

#include "Credentials.h"
#include <vector>

typedef struct RankingInfos  {
    int victories;
    std::string username;

}RankingInfos;

typedef struct PublicAccountInfos  {
    int victories, pnjKilled;
    std::string username;
    std::string friendList;
    std::string friendRequests;
    std::string pendingInvitation;
}PublicAccountInfos;


class Database {

private:
    const char* filename;
    sqlite3 *db;
    int rc;

public:
    Database(const char* filename);

    static int callback_counter(void *count, int argc, char **argv, char **azColName);
    static int callback_ranking(void *ptr, int argc, char **argv, char **azColName);
    static int callback_account_usrname(void *ptr, int argc, char **argv, char **azColName);

    int open();
    int insert_account(Credentials credentials);
    int get_nb_entries();
    bool is_identifiers_valid(Credentials credentials);
    std::vector<RankingInfos> getRanking();
    PublicAccountInfos getUsrInfosByUsrname(std::string);
    int sendFriendRequest(std::string username, std::string toAdd);
    int acceptFriendRequest(std::string username, std::string toAccept);
    std::string addToString(std::string original, std::string toAdd);
    std::string removeFromString(std::string original, std::string toAdd);


    void update_record();
    void delete_record();

    void testMethod();

    virtual ~Database();


};


#endif //PROJET_DATABASE_H
