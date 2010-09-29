set(CYBORG_CPP_FILES
    CyborgParser.cpp
    CyborgSource.cpp
    CyborgTcpSource.cpp
    )

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror")

qt4_wrap_cpp(mocfiles ${CYBORG_H_FULLPATHS})

include_directories(${CYBORG_H_PATH})
add_library(cyborg SHARED ${CYBORG_CPP_FILES} ${mocfiles} ${CYBORG_H_FULLPATHS})
target_link_libraries(cyborg ${QT_LIBRARIES})
install(TARGETS cyborg LIBRARY DESTINATION lib)
