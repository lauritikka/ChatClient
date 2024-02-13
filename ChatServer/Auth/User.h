//
// Created by vaige on 8.2.2024.
//

#ifndef CHATSERVER_USER_H
#define CHATSERVER_USER_H

#include <string>
#include <functional>

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
    std::string name;
    std::string password;
};

std::ostream& operator << (std::ostream& os, const User& lf)
{
    os << "Name: " << lf.name << '\n' << "Password: " << lf.password;
    return os;
}

std::size_t hash(const User& lf)
{
    std::hash<std::string> hash_fn;
    std::size_t hashValue = hash_fn(lf.name);
    boost::hash_combine(hashValue, hash_fn(lf.password));
    return hashValue;
}

#endif //CHATSERVER_USER_H
