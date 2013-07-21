cmake_minimum_required (VERSION 2.6)

project(FakeMouse)

set( MY_INCLUDES ${PROJECT_SOURCE_DIR}/include)

set( MY_SOURCES main.cpp src/FakeMouse.cpp )

include_directories( ${MY_INCLUDES} )

add_executable(fakeMouse ${MY_SOURCES})

target_link_libraries(fakeMouse X11 Xtst)