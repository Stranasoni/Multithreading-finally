cmake_minimum_required(VERSION 3.16.3)

project(socket_server VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(socket_server  
    main.cpp
 
)

