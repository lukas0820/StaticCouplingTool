## Add subdirectories
INCLUDE("${CMAKE_CURRENT_LIST_DIR}/language/filelist.cmake")
INCLUDE("${CMAKE_CURRENT_LIST_DIR}/coupling/filelist.cmake")
INCLUDE("${CMAKE_CURRENT_LIST_DIR}/application/filelist.cmake")

## Add include folders
LIST(APPEND INCLUDEDIRS
        "${UTILS_INCLUDEDIRS}"
        "${LANGUAGE_SPECIFIC_INCLUDEDIRS}"
        "${COUPLING_INCLUDEDIRS}"
        "${APPLICATION_INCLUDEDIRS}"
        )

## Add source files
LIST(APPEND SOURCE_FILES
        "${UTILS_SOURCE_FILES}"
        "${LANGUAGE_SPECIFIC_SOURCE_FILES}"
        "${COUPLING_SOURCE_FILES}"
        "${APPLICATION_SOURCE_FILES}"
        )

