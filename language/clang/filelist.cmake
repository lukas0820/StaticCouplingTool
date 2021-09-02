## Add include folders
LIST(APPEND LANGUAGE_SPECIFIC_INCLUDEDIRS
        "${CMAKE_CURRENT_LIST_DIR}"
        )

## Add source files
LIST(APPEND LANGUAGE_SPECIFIC_SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/ClangCouplingFinder.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/CouplingASTConsumer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/CouplingFrontendAction.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/CouplingVisitor.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/ClangCouplingFinder.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/CouplingASTConsumer.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/CouplingFrontendAction.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/CouplingVisitor.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/TypeSourceFinder.cpp"
        )
