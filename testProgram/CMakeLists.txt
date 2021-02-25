cmake_minimum_required(VERSION 3.17)
project(test_realm)

set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(test_realm test.cc)

target_link_libraries(test_realm ${CMAKE_THREAD_LIBS_INIT})