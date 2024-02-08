//
// Created by vaige on 7.2.2024.
//
#include "Room.h"
#include "Session.h"
#include <nlohmann/json.hpp>

void Room::addParticipant(Participant participant)
{
    mParticipants.insert(participant);
    sendParticipantInfo();
}

void Room::sendMessage(Participant sender, std::string message)
{
    for (auto& participant : mParticipants)
    {
            participant->sendMessage(message);
    }
}

void Room::removeParticipant(Room::Participant participant)
{
    mParticipants.erase(participant);
    sendParticipantInfo();
}

void Room::sendParticipantInfo()
{
    if (mParticipants.size() < 2) {
        return;
    }

    for (auto participant : mParticipants)
    {
        nlohmann::json peerInfo;

        for (const auto& peer : mParticipants)
        {
            if (peer != participant) {
                peerInfo["peers"].push_back(peer->getUserName());
            }
        }
        participant->sendMessage(peerInfo.dump());
    }
}
