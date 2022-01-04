cmake_minimum_required(VERSION 3.18)
project(POS_CHAT_GAB)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -pthread")

#Set your directories.  The dot representes the root application folder.
#Thus my the path to my domain folder:
set(APP_DOMAIN ./domain)
set(APP_CALC ./calc)

#Include the directories and now your cpp files will recognize your headers
include_directories(${APP_DOMAIN})
include_directories(${APP_CALC})
include_directories( ./src/include )

add_executable(POS_CHAT_GAB main.cpp Klient/Client.cpp Klient/Client.h Server/Server.cpp Server/Server.h SubMenus/SubMenus.cpp SubMenus/SubMenus.h Variables/BufferInput.cpp Klient/AccountClient.cpp Klient/AccountClient.h Server/AccountServer.cpp Server/AccountServer.h ${SOURCE_FILES} ${HEADER_FILES})

