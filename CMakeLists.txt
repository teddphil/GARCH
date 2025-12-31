cmake_minimum_required(VERSION 3.10)
project(garch_sp500)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(garch
    src/main.cpp
    src/garch.cpp
)