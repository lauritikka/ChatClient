//
// Created by vaige on 7.2.2024.
//

#include <nlohmann/json.hpp>
#include "Message.h"

nlohmann::json serializeMessage(const Message& msg)
{
    nlohmann::json j;
    j["name"] = msg.username;
    j["message"] = msg.payload;
    j["timeStamp"] = std::chrono::duration_cast<std::chrono::milliseconds>(msg.timeStamp.time_since_epoch()).count();
    return j;
}

Message deserializeMessage(const nlohmann::json& j)
{
    return Message{j["name"], j["message"], Clock::now()};
}