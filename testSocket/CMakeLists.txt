cmake_minimum_required(VERSION 3.16)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(testSocket)

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
)
FetchContent_GetProperties(boost)
if(NOT boost_POPULATED)
    message(STATUS "Populating boost...")
    FetchContent_Populate(boost)
    message(STATUS "Populate boost...")
    # Add here options for boost building
    set(BOOST_BUILD_TESTS OFF)
    message(STATUS "test disable boost...")
    add_subdirectory(${boost_SOURCE_DIR} ${boost_BINARY_DIR})
    message(STATUS "Done.")
endif()

include_directories(BEFORE SYSTEM ${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR}/include)

add_executable(testSocket src/main.cpp)

target_link_libraries(testSocket
    ${CMAKE_THREAD_LIBS_INIT}
    yaml-cpp
)