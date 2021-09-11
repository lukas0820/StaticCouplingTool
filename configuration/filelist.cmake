## Add include folders


LIST(APPEND APPLICATION_INCLUDEDIRS
        "${CMAKE_CURRENT_LIST_DIR}"
        )

## Add source files
LIST(APPEND APPLICATION_SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/CLIParser.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/ConfigurationManager.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/ConfigurationArgumentDatabase.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/JSONParser.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/ConfigurationExporter.cpp"
        )


## Add subdirectories
#INCLUDE("${CMAKE_CURRENT_LIST_DIR}/SUBDIR/filelist.cmake")