//
// Created by vaige on 13.2.2024.
//

#include "Db.h"
#include <SQLiteCpp/VariadicBind.h>
#include <iostream>
#include "User.h"

void Db::store(const User &user)
{
    mUsers.push_back(user);
    SQLite::Statement query(mDb, "INSERT INTO users VALUES (?, ?)");
    SQLite::bind(query, user.name, user.password);
    query.exec();
}

const std::vector<User> &Db::getUsers() const
{
    SQLite::Statement query(mDb, "SELECT * from user");

    // Loop to execute the query step by step, to get one a row of results at a time
    while (query.executeStep())
    {
        std::cout << "row ( ";
        for (int i = 0; i < query.getColumnCount(); ++i)
            std::cout << query.getColumn(i) << ", ";
        std::cout << std::endl;
    }

    return mUsers;
}

Db::Db()
: mDb("database.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    SQLite::Statement query(mDb, "SELECT * from user");

    // Loop to execute the query step by step, to get one a row of results at a time
    while (query.executeStep())
    {
        std::cout << "row ( ";
        for (int i = 0; i < query.getColumnCount(); ++i)
            std::cout << query.getColumn(i) << ", ";
        std::cout << std::endl;
        mUsers.push_back(User(query.getColumn(0).getString(), query.getColumn(1).getString()));
    }
}
