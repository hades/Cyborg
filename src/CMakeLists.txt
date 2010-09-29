set(CYBORG_CPP_FILES
    Cyborg.cpp
    main.cpp
    )

set(CYBORG_H_FILES
    Cyborg.h
    )

qt4_wrap_cpp(CYBORG_MOC_FILES ${CYBORG_H_FILES})

qt4_add_resources(CYBORG_RESOURCES ${CYBORG_QRC_FULLPATHS})

include_directories(${CMAKE_SOURCE_DIR}/libcyborg/include)
add_executable(qcyborg WIN32 ${CYBORG_CPP_FILES} ${CYBORG_H_FILES}
    ${CYBORG_MOC_FILES} ${CYBORG_RESOURCES})
target_link_libraries(qcyborg ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY} cyborg)
install(TARGETS qcyborg RUNTIME DESTINATION bin)
