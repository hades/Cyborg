cmake_minimum_required(VERSION 2.6.4)

project(cyborg)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(Qt4 4.6.0 COMPONENTS QtCore QtGui REQUIRED)
include(${QT_USE_FILE})

find_package(QCA2 REQUIRED)

add_subdirectory(libcyborg)
add_subdirectory(resources)
add_subdirectory(src)
add_subdirectory(ui)
