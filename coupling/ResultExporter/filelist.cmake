## Add include folders
LIST(APPEND COUPLING_INCLUDEDIRS
        "${CMAKE_CURRENT_LIST_DIR}"
        )

## Add source files
LIST(APPEND COUPLING_SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/CommandLineExporter.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/JSONExporter.cpp"

        )

## Add subdirectories
