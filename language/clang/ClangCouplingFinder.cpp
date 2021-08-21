#include "ClangCouplingFinder.hpp"

#include <clang/Tooling/Tooling.h>

#include <iostream>

#include "CouplingFrontendAction.hpp"

using clang::tooling::CompilationDatabase;

namespace language::cpp
{
ClangCouplingFinder::ClangCouplingFinder() : initStatus(InitStatus::NOT_INITIALIZED) {}

ClangCouplingFinder::InitStatus ClangCouplingFinder::init(const std::string& compilationDatabaseDir)
{
    InitStatus status = InitStatus::FAILED;
    std::string error = "";
    this->database = CompilationDatabase::autoDetectFromDirectory(compilationDatabaseDir, error);

    if (error.empty() && this->database)
    {
        status = InitStatus::OK;
    }

    this->initStatus = status;
    setSourceFiles(getCompilationDBFiles());

    return status;
}

ClangCouplingFinder::InitStatus ClangCouplingFinder::getInitStatus() const
{
    return initStatus;
}

std::vector<std::string> ClangCouplingFinder::getCompilationDBFiles() const
{
    std::vector<std::string> fileList;

    if (getInitStatus() == InitStatus::OK && this->database)
    {
        fileList = this->database->getAllFiles();
    }

    return fileList;
}

void ClangCouplingFinder::execute()
{
    if (getInitStatus() == InitStatus::OK)
    {
        clang::tooling::ClangTool tool(*database, database->getAllFiles());
        tool.setPrintErrorMessage(false);
        tool.run(clang::tooling::newFrontendActionFactory<language::cpp::CouplingFrontendAction>().get());
    }
}

void ClangCouplingFinder::registerCouplingCallback(size_t couplingId, language::CouplingCallback clb)
{
    if (clb)
    {
        this->callbackMap[couplingId] = clb;
    }
}

void ClangCouplingFinder::unregisterCouplingCallback(size_t couplingId)
{
    this->callbackMap.erase(couplingId);
}

std::vector<std::string> ClangCouplingFinder::getSourceFiles() const
{
    return sourceFiles;
}

void ClangCouplingFinder::setSourceFiles(const std::vector<std::string>& sourceFiles)
{
    this->sourceFiles = sourceFiles;
}

}  // namespace language::cpp