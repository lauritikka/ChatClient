//
// Created by vaige on 7.2.2024.
//

#ifndef CHATSERVER_SESSION_H
#define CHATSERVER_SESSION_H

#include <queue>
#include "../Common.h"
#include "../Fail.h"
#include "Room.h"


class session : public std::enable_shared_from_this<session>
{
    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;
    std::queue<std::string> mOutQueue;
    Room& mRoom;
    std::string mUserName;

public:
    // Take ownership of the socket
    session(tcp::socket&& socket, Room& room);

    ~session();

    // Start the asynchronous operation
    void
    run();

    void
    on_accept(beast::error_code ec);

    void
    do_read();

    void
    on_read(beast::error_code ec, std::size_t bytes_transferred);

    void sendMessage(const std::string& message);

    void doWrite();

    void
    on_write(beast::error_code ec, std::size_t bytes_transferred);

    const std::string& getUserName();
};

#endif //CHATSERVER_SESSION_H