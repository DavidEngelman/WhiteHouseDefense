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


class Database {

private:
    const char* filename;
    sqlite3 *db;
    int rc;

public:
    Database(const char* filename);

    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    static int callback_get_last_entry(void *count, int argc, char **argv, char **azColName);

    int open();
    int insert_account(const std::string& username, const std:: string& password);
    int get_last_entry();
    void update_record();
    void delete_record();


    virtual ~Database();


};


#endif //PROJET_DATABASE_H
