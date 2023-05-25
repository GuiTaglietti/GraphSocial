#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sqlite3.h>
#include "socialmedia.h"

namespace database{

class Database{
public:
    Database();
    Database(socialmedia::SocialMedia &sm);
    virtual ~Database();
    bool dbinit(socialmedia::SocialMedia &sm);
    bool dbshutdown(socialmedia::SocialMedia &sm);

private:
    sqlite3* db;
    bool open_database(const std::string &dbname);
    bool create_table();
    bool save_users(socialmedia::SocialMedia &sm);
    bool load_users(socialmedia::SocialMedia &sm);
    bool close_database();
};

} // namespace database

#endif  // DATABASE_H
