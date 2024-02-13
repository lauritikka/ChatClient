//
// Created by vaige on 7.2.2024.
//

#include "Session.h"
#include <nlohmann/json.hpp>
#include "Message.h"


session::session(tcp::socket&& socket, Room& room)
: ws_(std::move(socket)), mRoom{room}, mUserName("Anonymous")
{
}

session::~session()
{
    mRoom.removeParticipant(shared_from_this());
}

// Start the asynchronous operation
void session::run()
{
    ws_.set_option(
            websocket::stream_base::timeout::suggested(
                    beast::role_type::server));

    // Set a decorator to change the Server of the handshake
    ws_.set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res)
            {
                res.set(http::field::server,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-server-async");
            }));

    // Accept the websocket handshake
    ws_.async_accept(
            beast::bind_front_handler(
                    &session::on_accept,
                    shared_from_this()));

}

void
session::on_accept(beast::error_code ec)
{
    if(ec)
        return fail(ec, "accept");

    mRoom.addParticipant(shared_from_this());

    do_read();
}

void
session::do_read()
{
    // Read a message into our buffer
    ws_.async_read(
            buffer_,
            beast::bind_front_handler(
                    &session::on_read,
                    shared_from_this()));
}

void
session::on_read(
        beast::error_code ec,
        std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    // This indicates that the session was closed
    if(ec == websocket::error::closed)
        return;

    if(ec)
        return fail(ec, "read");

    std::string msg((char*)buffer_.data().data(), bytes_transferred);

    try {
        auto j = nlohmann::json::parse(msg);

        if (j.contains("username")) {
            mUserName = j["username"];
            auto tmpMsg = deserializeMessage(j);
            auto j2 = serializeMessage(tmpMsg);
            std::cout << "Message: " << j2.dump() << std::endl;
            mRoom.sendMessage(shared_from_this(), j2.dump());
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Failed to parse message: " << e.what() << std::endl;
    }

    std::cout << "Received message from " << mUserName << std::endl;

    buffer_.clear();
    do_read();
}

void session::sendMessage(const std::string &message)
{
    bool writeInProgress = !mOutQueue.empty();
    mOutQueue.push(message);
    if (!writeInProgress)
    {
        doWrite();
    }
}

void session::doWrite()
{
    ws_.async_write(
            boost::asio::buffer(mOutQueue.front()),
            beast::bind_front_handler(
                    &session::on_write,
                    shared_from_this()));
}

void
session::on_write(
        beast::error_code ec,
        std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if(ec)
        return fail(ec, "write");

    mOutQueue.pop();

   if (!mOutQueue.empty())
   {
       doWrite();
   }
}

const std::string& session::getUserName()
{
    return mUserName;
}