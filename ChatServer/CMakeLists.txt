cmake_minimum_required(VERSION 3.27)
project(ChatServer)

set(CMAKE_CXX_STANDARD 23)

find_package(nlohmann_json REQUIRED)
find_package(fmt REQUIRED)
find_package(SQLiteCpp CONFIG REQUIRED)

add_executable(ChatServer main.cpp
        Fail.h
        Chat/Room.cpp
        Chat/Listener.h
        Chat/Session.cpp
        Chat/Room.cpp
        Chat/Message.h
        Chat/Message.cpp
        Auth/Session.h
        Auth/Listener.h
        Auth/Db.h
        Auth/Db.cpp
        Auth/User.cpp
)

target_link_libraries(ChatServer PRIVATE nlohmann_json::nlohmann_json fmt::fmt)
target_link_libraries(ChatServer PRIVATE SQLiteCpp)