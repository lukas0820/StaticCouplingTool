#include "CouplingASTConsumer.hpp"

namespace language::cpp
{
CouplingASTConsumer::CouplingASTConsumer(clang::ASTContext* context) : visitor(context) {}


void CouplingASTConsumer::HandleTranslationUnit(clang::ASTContext& Context)
{
    this->visitor.TraverseDecl(Context.getTranslationUnitDecl());
}

}  // namespace language::cpp