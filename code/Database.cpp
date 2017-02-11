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


int Database::callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;

    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }


    printf("\n");
    return 0;
}

int Database::callback_get_last_entry(void *count, int argc, char **argv, char **azColName){
    int *c = (int*)count;
    *c = atoi(argv[0]);
    return 0;
}

int Database::insert_account(const std::string& username, const std:: string& password) {


    char *zErrMsg = 0;
    int id = get_last_entry() + 1;

    std::stringstream strm;

    strm << "insert into Accounts(id,username,password) values(" << id
         << ",'" << username << "','" << password << "')";


    std::string s = strm.str();
    char *str = &s[0];
    char *query = str;

    rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    else{
        fprintf(stdout, "Records created successfully\n");
    }



    return 0;
}

int Database::get_last_entry() {


    char *zErrMsg = 0;
    char *query = "select Count(*) from Accounts";
    int count = 1;

    rc = sqlite3_exec(db, query, callback_get_last_entry, &count, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return -1;
    }

    return count;

}

Database::~Database() {
    sqlite3_close(db);
}
