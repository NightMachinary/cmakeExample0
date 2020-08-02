cmake_minimum_required(VERSION 3.15)
project(labNIGHT)

set(CMAKE_CXX_STANDARD 20)

add_executable(labNIGHT main.cpp)

## use with specific path
#set(CURL_PATH "/usr/local/Cellar/curl/7.69.1/")
#find_library(
#        LIB_CURL
#        NAMES
#            curl
#        PATHS
#             ${CURL_PATH}/lib)
#
#target_link_libraries(labNIGHT ${LIB_CURL})
#
#target_include_directories(
#        labNIGHT
#        SYSTEM
#        PRIVATE "${CURL_PATH}/include")
##

##
include(FindPkgConfig)
pkg_check_modules(CURL libcurl REQUIRED)
include_directories(
        SYSTEM ${CURL_INCLUDE_DIRS}
)
target_link_libraries(labNIGHT
        PRIVATE ${CURL_LIBRARIES}
        )
##

if (APPLE)
    # This is a bug in CMake that causes it to prefer the system version over
    # the one in the specified ROOT folder.
    set(OPENSSL_ROOT_DIR ${OPENSSL_ROOT_DIR} /usr/local/opt/openssl@1.1)
    set(OPENSSL_CRYPTO_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libcrypto.dylib CACHE FILEPATH "" FORCE)
    set(OPENSSL_SSL_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libssl.dylib CACHE FILEPATH "" FORCE)
endif()

set(USE_SYSTEM_CURL "ON")

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git GIT_TAG c8d33915dbd88ad6c92b258869b03aba06587ff9) # the commit hash for 1.5.0
FetchContent_MakeAvailable(cpr)

target_link_libraries(labNIGHT PRIVATE cpr::cpr)
