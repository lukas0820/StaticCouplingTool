## Add include folders
LIST(APPEND COUPLING_INCLUDEDIRS
        "${CMAKE_CURRENT_LIST_DIR}"
        )

## Add source files
LIST(APPEND COUPLING_SOURCE_FILES
        #"${CMAKE_CURRENT_LIST_DIR}/foo.cpp"
        )

## Add subdirectories
#INCLUDE("${CMAKE_CURRENT_LIST_DIR}/SUBDIR/filelist.cmake")