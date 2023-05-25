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
    bool create_table();
    bool open_database(const std::string &dbname);
    bool delete_table();

private:
    sqlite3* db;
    bool save_users(socialmedia::SocialMedia &sm);
    bool load_users(socialmedia::SocialMedia &sm);
    bool close_database();
    bool save_links(socialmedia::SocialMedia &sm);
    bool load_links(socialmedia::SocialMedia &sm);
};

} // namespace database

#endif  // DATABASE_H
