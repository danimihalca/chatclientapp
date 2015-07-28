project(chatClientApp)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package (Threads)

INCLUDE_DIRECTORIES(${HEADERS_INSTALL_PATH})
LINK_DIRECTORIES(${LIBRARY_INSTALL_PATH})

SET (SRC_LIST src/main.cpp)

SET (LIBRARIES ${CMAKE_THREAD_LIBS_INIT}
               websockets
               chatClientAPI)

ADD_EXECUTABLE(${PROJECT_NAME} ${SRC_LIST})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
