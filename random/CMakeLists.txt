cmake_minimum_required(VERSION 3.24)
project(socket_comm_app)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE source_files CONFIGURE_DEPENDS "src/*.cpp")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_RELEASE_LIBS ON)
set(BOOST_ENABLE_CMAKE ON)
set(FETCHCONTENT_QUIET FALSE)
set(Boost_VERSION 1.81.0)
string(REPLACE "." "_" Boost_VERSION_underscore ${Boost_VERSION})
include(FetchContent)

FetchContent_Declare(
        Boost
        URL https://boostorg.jfrog.io/artifactory/main/release/${Boost_VERSION}/source/boost_${Boost_VERSION_underscore}.tar.gz
        USES_TERMINAL_DOWNLOAD TRUE
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(Boost)
set(BOOST_ROOT ${boost_SOURCE_DIR})

find_package(Boost ${Boost_VERSION} REQUIRED)

add_executable(socket_comm_app
        ${source_files} src/socket_comm_server.cpp src/socket_comm_server.hpp src/socket_comm_client.cpp src/socket_comm_client.hpp)
target_include_directories(socket_comm_app PUBLIC src)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(socket_comm_app ${Boost_LIBRARIES})
