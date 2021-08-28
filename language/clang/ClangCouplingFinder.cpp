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
        ExecutionArguments args;
        args.couplingCallback = [=](coupling::AbstractCoupling* coupling) { this->receiveCallback(coupling); };
        args.sourceFileList = this->sourceFiles;
        args.finishedTranslationUnitCallback = [=](const std::string& file)
        { this->finishedTranslationUnitCallback(file); };


        clang::tooling::ClangTool tool(*database, database->getAllFiles());
        tool.setPrintErrorMessage(false);
        tool.run(CouplingFrontendAction::createFrontendActionFactory(args).get());
    }
}

void ClangCouplingFinder::registerCouplingCallback(language::CouplingCallback clb)
{
    if (clb)
    {
        this->callback = clb;
    }
}


std::vector<std::string> ClangCouplingFinder::getSourceFiles() const
{
    return sourceFiles;
}

void ClangCouplingFinder::setSourceFiles(const std::vector<std::string>& sourceFiles)
{
    this->sourceFiles = sourceFiles;
}

void ClangCouplingFinder::receiveCallback(coupling::AbstractCoupling* coupling)
{
    if (this->callback)
    {
        this->callback(coupling);
    }
}

void ClangCouplingFinder::finishedTranslationUnitCallback(const std::string& file)
{
    static int i = 0;

    i++;

    std::cout << "file  " << i << " of " << this->sourceFiles.size() << std::endl;
}


}  // namespace language::cpp