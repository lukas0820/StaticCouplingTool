## Add include folders
LIST(APPEND LANGUAGE_SPECIFIC_INCLUDEDIRS
        "${CMAKE_CURRENT_LIST_DIR}"
        )

## Add source files
LIST(APPEND LANGUAGE_SPECIFIC_SOURCE_FILES
        #"${CMAKE_CURRENT_LIST_DIR}/foo.cpp"
        )

## Add subdirectories
INCLUDE("${CMAKE_CURRENT_LIST_DIR}/cpp/filelist.cmake")