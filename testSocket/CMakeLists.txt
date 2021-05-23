cmake_minimum_required(VERSION 3.16)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(socketApp)

set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include(FetchContent)
FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_SHALLOW	ON
        GIT_TAG yaml-cpp-0.6.3
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/inc/yaml-cpp
)
FetchContent_GetProperties(yaml-cpp)
if(NOT yaml-cpp_POPULATED)
    message(STATUS "Populating yaml-cpp...")
    FetchContent_Populate(yaml-cpp)
    # Add here options for yaml-cpp building
    set(YAML_CPP_BUILD_TESTS OFF)
    add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
    message(STATUS "Done.")
endif()

FetchContent_Declare(
        boost
        URL https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.gz
        PREFIX ${PROJECT_SOURCE_DIR}/inc/boost
        STAMP_DIR ${PROJECT_SOURCE_DIR}/inc/boost/log/
        BUILD_COMMAND ./bootstrap.sh
)
FetchContent_GetProperties(boost)
if(NOT boost_POPULATED)
    message(STATUS "Populating boost...")
    FetchContent_Populate(boost)
    message(STATUS "Populate boost...")
    # Add here options for boost building
    set(BOOST_BUILD_TESTS OFF)
    include_directories(${boost_SOURCE_DIR} ${boost_BINARY_DIR})
    message(STATUS "Done.")
endif()

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_SHALLOW	ON
        GIT_TAG v1.8.5
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/inc/spdlog
)
FetchContent_GetProperties(spdlog)
if(NOT spdlog_POPULATED)
    message(STATUS "Populating spdlog...")
    FetchContent_Populate(spdlog)
    # Add here options for spdlog building
    set(SPDLOG_BUILD_TESTS OFF)
    add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
    message(STATUS "Done.")
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(BEFORE SYSTEM
        ${yaml-cpp_SOURCE_DIR}
        ${yaml-cpp_BINARY_DIR}/include
        ${spdlog_SOURCE_DIR}
        ${spdlog_BINARY_DIR}/include)
set(SOURCE_FILES
        src/main.cpp
        src/Server.cpp
        src/CommandParser.cpp
        src/Message.h
        src/Endpoint.h)

add_executable(socketApp ${SOURCE_FILES})

target_link_libraries(socketApp
    ${CMAKE_THREAD_LIBS_INIT}
    yaml-cpp
    pthread
    spdlog
)