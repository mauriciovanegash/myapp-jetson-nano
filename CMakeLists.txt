cmake_minimum_required(VERSION 3.8)
project(myapp)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
if( NOT OpenCV_FOUND )
    message("-- didn't find OpenCV on system, disabling OpenCV")
else()
    message("-- OpenCV version:  " ${OpenCV_VERSION})
endif()

# setup build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-write-strings -Wno-deprecated-declarations")	# -std=c++14

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(myapp source/my_first_app.cpp)
target_link_libraries(myapp ${OpenCV_LIBS})

install(TARGETS myapp DESTINATION ${CMAKE_INSTALL_BINDIR})