set(CYBORG_CPP_FILES
    CyborgParser.cpp
    CyborgSource.cpp
    CyborgTcpSource.cpp
    CyborgUdpSource.cpp
    CyborgPassKey.cpp
    )

if(NOT WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror")
endif(NOT WIN32)

qt4_wrap_cpp(mocfiles ${CYBORG_H_FULLPATHS})

include_directories(${QCA2_INCLUDE_DIR})
include_directories(${CYBORG_H_PATH})
add_library(cyborg SHARED ${CYBORG_CPP_FILES} ${mocfiles} ${CYBORG_H_FULLPATHS})
target_link_libraries(cyborg ${QT_LIBRARIES} ${QCA2_LIBRARIES})
install(TARGETS cyborg DESTINATION lib)
