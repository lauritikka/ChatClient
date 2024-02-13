//
// Created by vaige on 13.2.2024.
//

#ifndef CHATSERVER_DB_H
#define CHATSERVER_DB_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>

struct User;

class Db
{
public:
    static Db& instance()
    {
        static Db db;
        return db;
    }

    void store(const User& user);
    [[nodiscard]] const std::vector<User>& getUsers() const;
private:
    Db();

    std::vector<User> mUsers;
    SQLite::Database mDb;
};


#endif //CHATSERVER_DB_H