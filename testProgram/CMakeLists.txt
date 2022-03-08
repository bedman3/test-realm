cmake_minimum_required(VERSION 3.17)
project(test_realm)

# include boost in this Cmake project
#
# note: the version number here is a bit of a hack to work around
# the fact that we can't just specify the version of a project
# we want to use.
include(ExternalProject)
ExternalProject_Add(BOOST VERSION "1.58.0"
  URL "https://github.com/boostorg/boost/archive/boost_1_58_0.tar.gz"
  SHA256 "5b5f5d8e5d9c8b5d7d7f5f7d7d7d7d7d7d7d7d7d7d7d7d7d7d7d7d7d7d7d7d7"
  CONFIGURE_COMMAND
  "./bootstrap.sh --with-libraries=filesystem,system,test,regex,chrono,thread,iostreams,graph,program_options,test,wave,random,log,algorithm,locale,date_time,atomic,chrono,fiber,lock,mutex,system,type_traits,experimental,core,parallel,log,chrono,program_options,test,wave,random,fiber,context,coroutine,execution,lock,mutex,system,type_traits,experimental,core,parallel,filesystem,test,regex,chrono,thread,iostreams,graph,program_options,test,wave,random,log,algorithm,locale,date_time,atomic,chrono,fiber,lock,mutex,system,type_traits,experimental,core,parallel"
  CONFIGURE_FLAGS
  "-DBOOST_LIBRARYDIR=lib -DBOOST_INCLUDEDIR=include -DBOOST_ROOT=$prefix"
  CONFIGURE_PATH
  "${prefix}/include"
  CONFIGURE_PATH
  "${prefix}/lib"
  CONFIGURE_PATH
  "${prefix}/lib64"
  CONFIGURE_PATH
  "${prefix}/lib/cmake"
  CONFIGURE_PATH
  "${prefix}/lib/pkgconfig"
  CONFIG
  "")

# link boost to this Cmake project


set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(test_realm test.cc)

target_link_libraries(test_realm ${CMAKE_THREAD_LIBS_INIT})