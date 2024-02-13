//
// Created by vaige on 8.2.2024.
//

#ifndef CHATSERVER_USER_H
#define CHATSERVER_USER_H

#include <string>
#include <functional>
#include <boost/functional/hash.hpp>

struct User
{
    explicit User(const std::string& rb)
    {
        const auto nameStart = rb.find_first_of('=') + 1;
        const auto separator = rb.find_first_of('&');
        const auto passStart = rb.find_last_of('=') + 1;

        name = std::string(rb.begin() + nameStart, rb.begin() + separator);
        password = std::string(rb.begin() + passStart, rb.end());
    }
    User(std::string name, std::string password)
    : name{std::move(name)}, password{std::move(password)}
    {}

    bool operator==(const User& rhs) const {
        return name == rhs.name && password == rhs.password;
    }

    std::string name;
    std::string password;
};

std::ostream& operator << (std::ostream& os, const User& lf);

std::size_t hash(const User& lf);

#endif //CHATSERVER_USER_H
