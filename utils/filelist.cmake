## Add include folders
LIST(APPEND UTILS_INCLUDEDIRS
        "${CMAKE_CURRENT_LIST_DIR}"
        )

## Add source files
LIST(APPEND UTILS_SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/FileUtils.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/ContainerUtils.cpp"
        )

## Add subdirectories
#INCLUDE("${CMAKE_CURRENT_LIST_DIR}/SUBDIR/filelist.cmake")