cmake_minimum_required(VERSION 3.3)
project(ClamCompIVassign6)

include_directories(/opt/include)
link_directories(/opt/lib)
link_libraries(/opt/lib/libxerces-c-3.1.dylib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp)

add_executable(ClamCompIVassign6 ${SOURCE_FILES})

