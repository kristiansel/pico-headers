cmake_minimum_required(VERSION 2.8)

project(pico-udpsocket-test)

include_directories(../)

set(MY_LINK_LIBRARIES "")
if(WIN32)
    set(MY_LINK_LIBRARIES "${MY_LINK_LIBRARIES} ws2_32")
endif(WIN32)

set(SERVER_TARGET "${PROJECT_NAME}-server")
add_executable(${SERVER_TARGET} "server.cpp")
target_link_libraries(${SERVER_TARGET} ${MY_LINK_LIBRARIES})

set(CLIENT_TARGET "${PROJECT_NAME}-client")
add_executable(${CLIENT_TARGET} "client.cpp")
target_link_libraries(${CLIENT_TARGET} ${MY_LINK_LIBRARIES})
