#include "CouplingASTConsumer.hpp"

namespace language::cpp
{
CouplingASTConsumer::CouplingASTConsumer(clang::ASTContext* context, ClangCouplingFinder::ExecutionArguments args)
    : visitor(context, args), args(args)
{
}


void CouplingASTConsumer::HandleTranslationUnit(clang::ASTContext& Context)
{
    clang::FullSourceLoc location = Context.getFullLoc(Context.getTranslationUnitDecl()->getBeginLoc());
    std::string fileName = "";
    if (location.getFileEntry())
    {
        fileName = location.getFileEntry()->getName().str();
    }

    if (this->args.startedTranslationUnitCallback)
    {
        this->args.startedTranslationUnitCallback(fileName);
    }

    this->visitor.TraverseDecl(Context.getTranslationUnitDecl());

    if(this->args.finishedTranslationUnitCallback)
    {
        this->args.finishedTranslationUnitCallback(fileName);
    }
}

}  // namespace language::cpp