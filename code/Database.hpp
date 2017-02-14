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


class Database {

private:
    const char* filename;
    sqlite3 *db;
    int rc;

public:
    Database(const char* filename);

    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    static int callback_counter(void *count, int argc, char **argv, char **azColName);
    static int callback_ranking(void *ptr, int argc, char **argv, char **azColName);

    int open();
    int insert_account(Credentials credentials);
    int get_nb_entries();
    bool is_identifiers_valid(Credentials credentials);
    std::vector<RankingInfos> getRanking();
    void update_record();
    void delete_record();

    void testMethod();

    virtual ~Database();


};


#endif //PROJET_DATABASE_H
