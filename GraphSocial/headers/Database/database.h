/**
 * @author Guilherme Martinelli Taglietti
 * @headerfile database.h (header file)
 * 
 * Database class using SQLite to save/load users/links in the application
 * Include guard
 * 
 * @attention SQLite3 is needed!
 * @include <sqlite3.h>
 * 
*/

#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>
#include "../SocialMedia/socialmedia.h"

namespace database{

class Database{
public:
    Database();
    Database(socialmedia::SocialMedia &sm);
    virtual ~Database();
    bool dbinit(socialmedia::SocialMedia &sm);
    bool drop_user(const std::string &s);
    bool save_user(const std::string &mail, const std::string &nme,
                   const std::string &brth, const std::string &phne,
                   const std::string &cty);
    bool save_link(const std::string &src, const std::string &dest);
    Database(const Database&) = delete;                 
    Database& operator=(const Database&) = delete;

private:
    sqlite3* db;
    bool load_users(socialmedia::SocialMedia &sm);
    bool close_database();
    bool load_links(socialmedia::SocialMedia &sm);
    bool create_table();
    bool open_database(const std::string &dbname);
    bool search_link(const std::string &src, const std::string &dest);
};

} // namespace database

#endif  // DATABASE_H
