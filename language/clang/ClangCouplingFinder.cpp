#include "ClangCouplingFinder.hpp"

#include <clang/Tooling/Tooling.h>

#include <iostream>

#include "ContainerUtils.hpp"
#include "CouplingFrontendAction.hpp"

using clang::tooling::CompilationDatabase;
using utils::ContainerUtils;

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
        this->sourceFiles = getFilesToAnalyse();

        ExecutionArguments args;
        args.couplingCallback = [=](coupling::AbstractCoupling* coupling) { this->receiveCallback(coupling); };
        args.sourceFileList = this->sourceFiles;
        args.finishedTranslationUnitCallback = [=](const std::string& file)
        { this->finishedTranslationUnitCallback(file); };
        args.merge = this->merge;

        clang::tooling::ClangTool tool(*database, this->sourceFiles);
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

void ClangCouplingFinder::registerProgressCallback(ProgressCallback clb)
{
    if (clb)
    {
        this->progressCallback = clb;
    }
}

void ClangCouplingFinder::mergeHeaderAndSourceFiles(bool merge)
{
    this->merge = merge;
}

void ClangCouplingFinder::setBlackList(const std::vector<std::string>& blackList)
{
    this->blackList = blackList;
}

void ClangCouplingFinder::setWhiteList(const std::vector<std::string>& whiteList)
{
    this->whiteList = whiteList;
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
    static int sourceFileCount = this->sourceFiles.size();

    i++;

    if(this->progressCallback)
    {
        this->progressCallback(i, sourceFileCount, file);
    }
}

std::vector<std::string> ClangCouplingFinder::getFilesToAnalyse()
{
    std::vector<std::string> returnList;

    auto whiteListCopy = this->whiteList;
    auto compilationDBFiles = getCompilationDBFiles();

    if (!whiteListCopy.empty())
    {
        for (auto blackListEntry : this->blackList)
        {
            if (ContainerUtils::isInVector<std::string>(whiteListCopy, blackListEntry))
            {
                whiteListCopy.erase(std::remove(whiteListCopy.begin(), whiteListCopy.end(), blackListEntry),
                                    whiteListCopy.end());
            }
        }

        returnList = whiteListCopy;
    }
    else
    {
        for (auto blackListEntry : this->blackList)
        {
            if (ContainerUtils::isInVector<std::string>(compilationDBFiles, blackListEntry))
            {
                compilationDBFiles.erase(
                    std::remove(compilationDBFiles.begin(), compilationDBFiles.end(), blackListEntry),
                    compilationDBFiles.end());
            }
        }

        returnList = compilationDBFiles;
    }

    return returnList;
}


}  // namespace language::cpp