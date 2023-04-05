CMAKE_MINIMUM_REQUIRED(VERSION 3.24)
PROJECT(socket_comm_app)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

FILE(GLOB_RECURSE source_files CONFIGURE_DEPENDS "src/*.cpp")

SET(FETCHCONTENT_QUIET FALSE)
INCLUDE(FetchContent)

# import spdlog
SET(spdlog_VERSION 1.11.0)
FETCHCONTENT_DECLARE(
        spdlog
        URL https://github.com/gabime/spdlog/archive/refs/tags/v${spdlog_VERSION}.tar.gz
        USES_TERMINAL_DOWNLOAD TRUE
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FETCHCONTENT_MAKEAVAILABLE(spdlog)

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

# import boost
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)
SET(Boost_USE_RELEASE_LIBS ON)
SET(BOOST_ENABLE_CMAKE ON)
SET(Boost_VERSION 1.81.0)
STRING(REPLACE "." "_" Boost_VERSION_underscore ${Boost_VERSION})
FETCHCONTENT_DECLARE(
        Boost
        URL https://boostorg.jfrog.io/artifactory/main/release/${Boost_VERSION}/source/boost_${Boost_VERSION_underscore}.tar.gz
        USES_TERMINAL_DOWNLOAD TRUE
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FETCHCONTENT_MAKEAVAILABLE(Boost)
SET(BOOST_ROOT ${boost_SOURCE_DIR})

FIND_PACKAGE(Boost ${Boost_VERSION} REQUIRED)

ADD_EXECUTABLE(socket_comm_app
        ${source_files})
TARGET_INCLUDE_DIRECTORIES(socket_comm_app PUBLIC src)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${spdlog_SOURCE_DIR}/include)
TARGET_LINK_LIBRARIES(socket_comm_app ${Boost_LIBRARIES})
