//
// Created by vaige on 7.2.2024.
//

#ifndef CHATSERVER_LISTENER_H
#define CHATSERVER_LISTENER_H


#include "../Common.h"
#include "Room.h"
#include "Session.h"
#include "../Fail.h"


namespace Chat
{
    // Accepts incoming connections and launches the sessions
    class listener : public std::enable_shared_from_this<listener>
    {
        net::io_context &ioc_;
        tcp::acceptor acceptor_;
        Room mRoom;

    public:
        listener(
                net::io_context &ioc,
                tcp::endpoint endpoint)
                : ioc_(ioc), acceptor_(ioc)
        {
            beast::error_code ec;

            // Open the acceptor
            acceptor_.open(endpoint.protocol(), ec);
            if (ec) {
                fail(ec, "open");
                return;
            }

            // Allow address reuse
            acceptor_.set_option(net::socket_base::reuse_address(true), ec);
            if (ec) {
                fail(ec, "set_option");
                return;
            }

            // Bind to the server address
            acceptor_.bind(endpoint, ec);
            if (ec) {
                fail(ec, "bind");
                return;
            }

            // Start listening for connections
            acceptor_.listen(
                    net::socket_base::max_listen_connections, ec);
            if (ec) {
                fail(ec, "listen");
                return;
            }
        }

        // Start accepting incoming connections
        void
        run()
        {
            do_accept();
        }

    private:
        void
        do_accept()
        {
            // The new connection gets its own strand
            acceptor_.async_accept(
                    ioc_,
                    beast::bind_front_handler(
                            &listener::on_accept,
                            shared_from_this()));
        }

        void
        on_accept(beast::error_code ec, tcp::socket socket)
        {
            if (ec) {
                fail(ec, "accept");
            } else {
                std::cout << "Connected" << std::endl;
                // Create the session and run it
                std::make_shared<session>(std::move(socket), mRoom)->run();
            }

            // Accept another connection
            do_accept();
        }
    };
}

#endif //CHATSERVER_LISTENER_H
