cmake_minimum_required (VERSION 2.6)

# find_package (LEAP)
set(LIBLEAP_INCLUDE_DIRS "/home/nathan/Leap_Developer_Kit_0.8.0_5300_Linux/LeapSDK/include")
set(LIBLEAP_LIBRARIES "/home/nathan/Leap_Developer_Kit_0.8.0_5300_Linux/LeapSDK/lib/x64/libLeap.so")

project(FakeMouse)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set( MY_INCLUDES ${PROJECT_SOURCE_DIR}/include)

set( MY_SOURCES main.cpp src/FakeMouse.cpp )

include_directories( ${MY_INCLUDES} ${LIBLEAP_INCLUDE_DIRS})

add_executable(fakeMouse ${MY_SOURCES})

target_link_libraries(fakeMouse X11 Xtst ${LIBLEAP_LIBRARIES})
