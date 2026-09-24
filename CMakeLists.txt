cmake_minimum_required(VERSION 4.3)
project(DDLplaylist)

set(CMAKE_CXX_STANDARD 20)

add_executable(DDLplaylist main.cpp
        Song.cpp
        Song.h
        Playlist.cpp
        Playlist.h
        DNode.cpp
        DNode.h
        DLL.cpp
        DLL.h)
