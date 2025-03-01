//
// Created by vaige on 8.2.2024.
//

#ifndef CHATSERVER_AUTH_LISTENER_H
#define CHATSERVER_AUTH_LISTENER_H

#include <memory>
#include "../Common.h"
#include "../Fail.h"
#include "Session.h"


namespace Auth
{

    class Listener : public std::enable_shared_from_this<Listener>
    {
        net::io_context& ioc_;
        tcp::acceptor acceptor_;
        std::shared_ptr<std::string const> doc_root_;

    public:
        Listener(
                net::io_context& ioc,
                tcp::endpoint endpoint,
                std::shared_ptr<std::string const> const& doc_root)
                : ioc_(ioc)
                , acceptor_(net::make_strand(ioc))
                , doc_root_(doc_root)
        {
            beast::error_code ec;

            // Open the acceptor
            acceptor_.open(endpoint.protocol(), ec);
            if(ec)
            {
                fail(ec, "open");
                return;
            }

            // Allow address reuse
            acceptor_.set_option(net::socket_base::reuse_address(true), ec);
            if(ec)
            {
                fail(ec, "set_option");
                return;
            }

            // Bind to the server address
            acceptor_.bind(endpoint, ec);
            if(ec)
            {
                fail(ec, "bind");
                return;
            }

            // Start listening for connections
            acceptor_.listen(
                    net::socket_base::max_listen_connections, ec);
            if(ec)
            {
                fail(ec, "listen");
                return;
            }
        }

        // Start accepting incoming connections
        void
        run()
        {
            std::cout << "Accepting connections" << std::endl;
            do_accept();
        }

    private:
        void
        do_accept()
        {
            // The new connection gets its own strand
            acceptor_.async_accept(
                    net::make_strand(ioc_),
                    beast::bind_front_handler(
                            &Listener::on_accept,
                            shared_from_this()));
        }

        void
        on_accept(beast::error_code ec, tcp::socket socket)
        {
            if(ec)
            {
                fail(ec, "accept");
                return; // To avoid infinite loop
            }
            else
            {
                std::cout << "Client connected" << std::endl;
                // Create the session and run it
                std::make_shared<Session>(
                        std::move(socket),
                        doc_root_)->run();
            }

            // Accept another connection
            do_accept();
        }
    };

}

#endif //CHATSERVER_LISTENER_H
