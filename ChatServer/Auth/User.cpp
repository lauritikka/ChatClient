//
// Created by vaige on 13.2.2024.
//
#include "User.h"


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