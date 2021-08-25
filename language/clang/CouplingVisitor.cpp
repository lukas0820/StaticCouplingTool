#include "CouplingVisitor.hpp"

#include <iostream>

#include "ContainerUtils.hpp"
#include "FileUtils.hpp"

using std::string;

using clang::ASTContext;
using clang::FullSourceLoc;

using utils::ContainerUtils;
using utils::FileUtils;


namespace language
{
namespace cpp
{
CouplingVisitor::CouplingVisitor(ASTContext* Context, ClangCouplingFinder::ExecutionArguments args)
    : context(Context), executionArguments(args)
{
    init();
}

void CouplingVisitor::init()
{
    for (std::string s : this->executionArguments.sourceFileList)
    {
        sourceFiles.push_back(FileUtils::removeFileExtension(s));
    }
}


bool CouplingVisitor::isCoupling(const clang::SourceLocation& caller, const clang::SourceLocation& callee) const
{
    bool callerNameNotEmpty = false;

    bool calleeNameNotEmpty = false;
    bool sourceFilesContainsCallee = false;

    bool isCallFromCurrentFile = false;


    clang::FullSourceLoc FullLocation = context->getFullLoc(caller);
    clang::FileID fileID = FullLocation.getFileID();
    unsigned int thisFileID = fileID.getHashValue();
    isCallFromCurrentFile = thisFileID == 1;

    std::string callerFileName = getStatementFileName(caller);
    callerNameNotEmpty = !callerFileName.empty();


    std::string calleeFileName = getStatementFileName(callee);
    std::string fileNameWithoutExtension = FileUtils::removeFileExtension(calleeFileName);
    calleeNameNotEmpty = !fileNameWithoutExtension.empty();
    sourceFilesContainsCallee = ContainerUtils::isInVector<std::string>(this->sourceFiles, fileNameWithoutExtension);


    return isCallFromCurrentFile && sourceFilesContainsCallee && calleeNameNotEmpty && callerNameNotEmpty;
}

bool CouplingVisitor::VisitCallExpr(clang::CallExpr* call)
{
    if (call && call->getDirectCallee())
    {
        clang::SourceLocation caller = call->getBeginLoc();
        clang::SourceLocation callee = call->getDirectCallee()->getBeginLoc();

        if (isCoupling(caller, callee))
        {
            std::string callerName = getStatementFileName(caller);
            std::string calleeName = getStatementFileName(callee);

            coupling::FileCoupling coupling(callerName, calleeName);
            this->executionArguments.couplingCallback(&coupling);
        }
    }


    return true;
}

bool CouplingVisitor::VisitCXXConstructExpr(clang::CXXConstructExpr* call)
{
    if (call && call->getConstructor())
    {
        clang::SourceLocation caller = call->getBeginLoc();
        clang::SourceLocation callee = call->getConstructor()->getBeginLoc();

        if (isCoupling(caller, callee))
        {
            std::string callerName = getStatementFileName(caller);
            std::string calleeName = getStatementFileName(callee);

            coupling::FileCoupling coupling(callerName, calleeName);
            this->executionArguments.couplingCallback(&coupling);
        }
    }


    return true;
}

std::string CouplingVisitor::getStatementFileName(const clang::SourceLocation& sourceLocation) const
{
    std::string fileName = "";
    clang::FullSourceLoc location = this->context->getFullLoc(sourceLocation);
    if (location.getFileEntry())
    {
        fileName = location.getFileEntry()->getName().str();
    }

    return fileName;
}


}  // namespace cpp
}  // namespace language
