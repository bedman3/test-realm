cmake_minimum_required(VERSION 3.17)
project(testSocket)

set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(testSocket src/main.cpp)

target_link_libraries(testSocket ${CMAKE_THREAD_LIBS_INIT})