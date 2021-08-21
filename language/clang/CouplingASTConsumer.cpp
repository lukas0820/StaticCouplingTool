#include "CouplingASTConsumer.hpp"

namespace language::cpp
{
CouplingASTConsumer::CouplingASTConsumer(clang::ASTContext* context, ClangCouplingFinder::ExecutionArguments args)
    : visitor(context, args)
{
}


void CouplingASTConsumer::HandleTranslationUnit(clang::ASTContext& Context)
{
    this->visitor.TraverseDecl(Context.getTranslationUnitDecl());
}

}  // namespace language::cpp