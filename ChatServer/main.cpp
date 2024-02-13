#include "Chat/Session.h"
#include "Chat/Listener.h"
#include "Common.h"
#include "Auth/Listener.h"


int main(int argc, char* argv[])
{
    auto const address = net::ip::make_address("0.0.0.0");
    auto const wsPort = static_cast<unsigned short>(6969);
    const auto httpPort = static_cast<unsigned short>(8080);
    const auto docRoot = "../../";

    // The io_context is required for all I/O
    net::io_context ioc;

    // Create and launch a listening port
    std::make_shared<Chat::listener>(ioc, tcp::endpoint{address, wsPort})->run();
//    std::make_shared<Auth::Listener>(ioc, tcp::endpoint{address, httpPort}, std::make_shared<std::string>(docRoot))->run();

    ioc.run();

    return EXIT_SUCCESS;
}