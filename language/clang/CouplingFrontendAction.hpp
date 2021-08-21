#ifndef STATICCPPCOUPLING_COUPLINGFRONTENDACTION_HPP
#define STATICCPPCOUPLING_COUPLINGFRONTENDACTION_HPP

#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>
#include <clang/Tooling/Tooling.h>

#include "ClangCouplingFinder.hpp"
#include "CouplingASTConsumer.hpp"

namespace language::cpp
{
class CouplingFrontendAction : public clang::ASTFrontendAction
{
public:
    CouplingFrontendAction(ClangCouplingFinder::ExecutionArguments args);
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& compiler,
                                                                  llvm::StringRef file);

    static std::unique_ptr<clang::tooling::FrontendActionFactory> createFrontendActionFactory(
        ClangCouplingFinder::ExecutionArguments args);

private:
    ClangCouplingFinder::ExecutionArguments executionArguments;
};

}  // namespace language::cpp


#endif  // STATICCPPCOUPLING_COUPLINGFRONTENDACTION_HPP
