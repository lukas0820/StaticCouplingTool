#include "CouplingFrontendAction.hpp"


namespace language::cpp
{
std::unique_ptr<clang::ASTConsumer> CouplingFrontendAction::CreateASTConsumer(clang::CompilerInstance& compiler,
                                                                              llvm::StringRef file)
{
    return std::make_unique<CouplingASTConsumer>(&compiler.getASTContext());
}

}  // namespace language::cpp