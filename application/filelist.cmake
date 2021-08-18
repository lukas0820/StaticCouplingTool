## Add include folders
LIST(APPEND APPLICATION_INCLUDEDIRS
        "${CMAKE_CURRENT_LIST_DIR}"
        )

## Add source files
LIST(APPEND APPLICATION_SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/main-coupling.cpp"
        )

## Add subdirectories
#INCLUDE("${CMAKE_CURRENT_LIST_DIR}/SUBDIR/filelist.cmake")