set(CYBORG_H_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CYBORG_H_FILES
    CyborgParser.h
    CyborgSource.h
    CyborgTcpSource.h
    CyborgUdpSource.h
    )

set(CYBORG_H_FULLPATHS)
foreach(hfile ${CYBORG_H_FILES})
    set(thfile ${CYBORG_H_PATH}/${hfile})
    list(APPEND CYBORG_H_FULLPATHS ${thfile})
endforeach(hfile ${CYBORG_H_FILES})

set(CYBORG_H_FILES ${CYBORG_H_FILES} PARENT_SCOPE)
set(CYBORG_H_PATH ${CYBORG_H_PATH} PARENT_SCOPE)
set(CYBORG_H_FULLPATHS ${CYBORG_H_FULLPATHS} PARENT_SCOPE)

install(DIRECTORY ./ DESTINATION include/cyborg
        FILES_MATCHING PATTERN "*.h")
