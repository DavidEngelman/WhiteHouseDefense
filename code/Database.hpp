//
// Created by david on 11/02/17.
//

#ifndef PROJET_DATABASE_H
#define PROJET_DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <iostream>
#include <string.h>


class Database {

private:
    std::string filename;

public:
    Database();
    int open();
    void insert_record();
    void update_record();
    void delete_record();


    virtual ~Database();


};


#endif //PROJET_DATABASE_H
