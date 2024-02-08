//
// Created by vaige on 7.2.2024.
//

#ifndef CHATSERVER_ROOM_H
#define CHATSERVER_ROOM_H

#include <set>
#include <string>
#include <memory>


class session;


class Room
{
public:
    using Participant = std::shared_ptr<session>;

    void addParticipant(Participant participant);
    void removeParticipant(Participant participant);

    void sendMessage(Participant sender, std::string message);

private:
    void sendParticipantInfo();
    std::set<Participant> mParticipants{};
};

#endif //CHATSERVER_ROOM_H
