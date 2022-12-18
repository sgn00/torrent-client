cmake_minimum_required(VERSION 3.16)
project(TorrentClient)

set(CMAKE_CXX_STANDARD 17)

# # bencoding
add_library(bencoding INTERFACE)
target_include_directories(bencoding INTERFACE lib/)

# # SHA1
add_library(sha INTERFACE)
target_include_directories(sha INTERFACE lib/)

# boost
find_package(Boost REQUIRED COMPONENTS system thread)

# CPR
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG a2d35a1cb9f3f7e2f1469d6a189751331dc99f96) 
FetchContent_MakeAvailable(cpr)

file(GLOB sources src/*.cpp src/*.h)
add_executable(torrent-client ${sources})
target_include_directories(torrent-client PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(torrent-client PRIVATE ${Boost_LIBRARIES} bencoding sha cpr::cpr)



