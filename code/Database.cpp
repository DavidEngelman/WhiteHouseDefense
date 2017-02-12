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

int Database::callback_counter(void *count, int argc, char **argv, char **azColName){
    int *c = (int*)count;
    *c = atoi(argv[0]);
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

    rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
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

Database::~Database() {
    sqlite3_close(db);
}
