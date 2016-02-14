cmake_minimum_required(VERSION 3.3)
project(ClamXMLParserv5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    custom.xml
    main.cpp
    Makefile
    new_xml.xml
    str_manip_funcs.cpp
    str_manip_funcs.h
    XMLElement.cpp
    XMLElement.h
    XMLParser.cpp
    XMLParser.h)

add_executable(ClamXMLParserv5 ${SOURCE_FILES})