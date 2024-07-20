cmake_minimum_required(VERSION 3.16.3)

project(multi_thread VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(multi_thread 
    src/main.cpp
    src/Buffer.h
    src/Buffer.cpp
    src/Client.h
    src/Client.cpp
)
find_package(Threads REQUIRED)
target_link_libraries(multi_thread PRIVATE Threads::Threads)

# cmake_minimum_required(VERSION 3.16.3)

# project(socket_server VERSION 1.0.0 LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_executable(socket_server  
#     src/Server.cpp
 
# )


