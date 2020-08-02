cmake_minimum_required(VERSION 3.15)
project(labNIGHT)

set(CMAKE_CXX_STANDARD 20)

add_executable(labNIGHT main.cpp)

set(CURL_PATH "/usr/local/Cellar/curl/7.69.1/")
find_library(
        LIB_CURL
        NAMES
            curl
        PATHS
             ${CURL_PATH}/lib)

target_link_libraries(labNIGHT ${LIB_CURL})

target_include_directories(
        labNIGHT
        SYSTEM
        PRIVATE "${CURL_PATH}/include")
