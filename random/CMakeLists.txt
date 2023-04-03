cmake_minimum_required(VERSION 3.10)
project(socket_comm_app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE source_files CONFIGURE_DEPENDS "src/*.cpp")

add_executable(socket_comm_app
        ${source_files})

target_include_directories(socket_comm_app PUBLIC src)