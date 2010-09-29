cmake_minimum_required(VERSION 2.6.4)

project(libcyborg)

find_package(Qt4 4.4.0 COMPONENTS QtCore QtNetwork REQUIRED)
include(${QT_USE_FILE})

add_subdirectory(include)
add_subdirectory(src)
