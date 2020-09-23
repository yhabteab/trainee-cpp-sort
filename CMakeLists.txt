cmake_minimum_required(VERSION 3.10)
project(cpp-sort LANGUAGES CXX)

set(BOOST_MIN_VERSION "1.66.0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# TODO: If you have any problems with boost you can comment out this line
# TODO: And add the absolute path to your Boost library
#set(BOOST_INCLUDEDIR /Users/username/Downloads/boost_1_66_0)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(Boost ${BOOST_MIN_VERSION} REQUIRED)

link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

set(DEPENDENCIES ${CMAKE_DL_LIBS} ${Boost_LIBRARIES})

set(ReSOURCES main.cpp)

add_executable(cpp-sort ${ReSOURCES})

target_link_libraries(cpp-sort ${DEPENDENCIES})

install(TARGETS cpp-sort)
