//
// Created by lukas on 11.08.21.
//

#include "ClangCouplingFinder.hpp"

#include <clang/Tooling/CompilationDatabase.h>
#include <clang/Tooling/Tooling.h>

#include "CouplingFrontendAction.hpp"

using clang::tooling::CompilationDatabase;


ClangCouplingFinder::ClangCouplingFinder(const std::string& compilationDatabaseDir,
                                         const std::vector<std::string>& sourceFiles)
    : compilationDatabaseDir(compilationDatabaseDir), sourceFiles(sourceFiles)
{
}


void ClangCouplingFinder::execute()
{
    std::string error = "";
    std::unique_ptr<CompilationDatabase> database =
        CompilationDatabase::autoDetectFromDirectory(this->compilationDatabaseDir, error);
    if (error.empty())
    {
        clang::tooling::ClangTool tool(*database, this->sourceFiles);
        tool.setPrintErrorMessage(false);
        tool.run(clang::tooling::newFrontendActionFactory<language::cpp::CouplingFrontendAction>().get());
    }
}
