cmake_minimum_required(VERSION 3.27)
project(ChatServer)

set(CMAKE_CXX_STANDARD 23)

find_package(nlohmann_json REQUIRED)
find_package(fmt REQUIRED)

add_executable(ChatServer main.cpp
        Fail.h
        Chat/Room.cpp
        Chat/Listener.h
        Chat/Session.cpp
        Chat/Room.cpp
        Chat/Message.h
        Chat/Message.cpp
        Auth/Session.h
        Auth/Listener.h)

target_link_libraries(ChatServer PRIVATE nlohmann_json::nlohmann_json fmt::fmt)