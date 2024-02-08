//
// Created by vaige on 7.2.2024.
//

#ifndef CHATSERVER_FAIL_H
#define CHATSERVER_FAIL_H

#include "Common.h"

static void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

#endif //CHATSERVER_FAIL_H
