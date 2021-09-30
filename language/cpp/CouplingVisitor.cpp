#include "CouplingVisitor.hpp"

#include "ContainerUtils.hpp"
#include "FileUtils.hpp"
#include <clang/Basic/FileEntry.h>

#include <iostream>

using std::string;

using clang::ASTContext;
using clang::FullSourceLoc;

using shared::ContainerUtils;
using shared::FileUtils;


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
        sourceFiles.push_back(FileUtils::getFileNameWithoutExtensionFromPath(s));
    }
}


bool CouplingVisitor::isCoupling(const clang::SourceLocation& caller, const clang::SourceLocation& callee) const
{
    bool callerNameNotEmpty = false;

    bool calleeNameNotEmpty = false;
    bool sourceFilesContainsCallee = false;

    bool isCallFromCurrentFile = false;

    bool callInSameFile = true;

    clang::FullSourceLoc FullLocation = context->getFullLoc(caller);
    clang::FileID fileID = FullLocation.getFileID();
    unsigned int thisFileID = fileID.getHashValue();
    isCallFromCurrentFile = thisFileID == 1;

    std::string callerFileName = getSourceLocationFileName(caller);
    callerNameNotEmpty = !callerFileName.empty();

    std::string calleeFileName = getSourceLocationFileName(callee);
    std::string fileNameWithoutExtension = FileUtils::getFileNameWithoutExtensionFromPath(calleeFileName);
    calleeNameNotEmpty = !fileNameWithoutExtension.empty();
    sourceFilesContainsCallee = ContainerUtils::isInVector<std::string>(this->sourceFiles, fileNameWithoutExtension);

    bool filteredByMergeArgument =
        this->executionArguments.merge && (FileUtils::getFileNameWithoutExtensionFromPath(callerFileName)) ==
                                              (FileUtils::getFileNameWithoutExtensionFromPath(calleeFileName));

    callInSameFile = callerFileName == calleeFileName;

    return isCallFromCurrentFile && sourceFilesContainsCallee && calleeNameNotEmpty && callerNameNotEmpty &&
           !callInSameFile && !filteredByMergeArgument;
}


bool CouplingVisitor::VisitCXXConstructExpr(clang::CXXConstructExpr* call)
{
    if (call && call->getConstructor())
    {
        clang::SourceLocation caller = call->getBeginLoc();
        clang::SourceLocation callee = call->getConstructor()->getBeginLoc();

        if (isCoupling(caller, callee))
        {
            std::string callerName = getSourceLocationFileName(caller);
            std::string calleeName = getSourceLocationFileName(callee);

            shared::FileCoupling coupling(callerName, calleeName);
            this->executionArguments.couplingCallback(&coupling);
        }
    }


    return true;
}

bool CouplingVisitor::VisitDeclRefExpr(clang::DeclRefExpr* call)
{
    if (call && call->getReferencedDeclOfCallee())
    {
        clang::SourceLocation caller = call->getBeginLoc();
        clang::SourceLocation callee = call->getReferencedDeclOfCallee()->getBeginLoc();

        if (isCoupling(caller, callee))
        {
            std::string callerName = getSourceLocationFileName(caller);
            std::string calleeName = getSourceLocationFileName(callee);

            shared::FileCoupling coupling(callerName, calleeName);
            this->executionArguments.couplingCallback(&coupling);
        }
    }


    return true;
}

bool CouplingVisitor::VisitCXXRecordDecl(clang::CXXRecordDecl* call)
{
    if (isInCurrentFile(call->getBeginLoc()) && call->bases_begin())
    {
        clang::SourceLocation caller = call->getBeginLoc();

        for (const auto& item : call->bases())
        {
            clang::SourceLocation callee = item.getType()->getAsCXXRecordDecl()->getBeginLoc();

            if (isCoupling(caller, callee))
            {
                std::string callerName = getSourceLocationFileName(caller);
                std::string calleeName = getSourceLocationFileName(callee);

                shared::FileCoupling coupling(callerName, calleeName);
                this->executionArguments.couplingCallback(&coupling);
            }
        }
    }


    return true;
}

bool CouplingVisitor::VisitCXXMemberCallExpr(clang::CXXMemberCallExpr* call)
{

    if (call && call->getRecordDecl())
    {
        clang::SourceLocation caller = call->getBeginLoc();
        clang::SourceLocation callee = call->getRecordDecl()->getBeginLoc();
        std::string callerName = getSourceLocationFileName(caller);
        std::string calleeName = getSourceLocationFileName(callee);


        if (isCoupling(caller, callee))
        {
            shared::FileCoupling coupling(callerName, calleeName);
            this->executionArguments.couplingCallback(&coupling);
        }
    }

    return true;
}


bool CouplingVisitor::isInCurrentFile(const clang::SourceLocation& sourceLocation) const
{
    clang::FullSourceLoc FullLocation = context->getFullLoc(sourceLocation);
    return FullLocation.getFileID().getHashValue() == 1;
}

std::string CouplingVisitor::getSourceLocationFileName(const clang::SourceLocation& sourceLocation) const
{
    std::string fileName = "";
    clang::FullSourceLoc location = this->context->getFullLoc(sourceLocation);
    if (location.getFileEntry())
    {
        fileName = location.getFileEntry()->getName().str();
        if (this->executionArguments.merge)
        {
            fileName = FileUtils::getFileNameWithoutExtensionFromPath(fileName);
        }
        else
        {
            fileName = FileUtils::getFileNameFromPath(fileName);
        }
    }

    return fileName;
}


}  // namespace cpp
}  // namespace language
