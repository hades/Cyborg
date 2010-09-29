cmake_minimum_required(VERSION 2.6.4)

project(cyborg)

find_package(Qt4 4.6.0 COMPONENTS QtCore QtGui REQUIRED)
include(${QT_USE_FILE})

add_subdirectory(libcyborg)
add_subdirectory(resources)
add_subdirectory(src)
add_subdirectory(ui)
