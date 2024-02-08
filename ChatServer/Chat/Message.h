//
// Created by vaige on 7.2.2024.
//

#ifndef CHATSERVER_MESSAGE_H
#define CHATSERVER_MESSAGE_H

#include <string>
#include <nlohmann/json_fwd.hpp>
#include <chrono>

using Clock = std::chrono::system_clock;

struct Message
{
    std::string username;
    std::string payload;
    Clock::time_point timeStamp;
};

nlohmann::json serializeMessage(const Message& msg);
Message deserializeMessage(const nlohmann::json& j);


#endif //CHATSERVER_MESSAGE_H
