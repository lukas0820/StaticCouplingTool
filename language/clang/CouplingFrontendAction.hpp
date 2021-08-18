#ifndef STATICCPPCOUPLING_COUPLINGFRONTENDACTION_HPP
#define STATICCPPCOUPLING_COUPLINGFRONTENDACTION_HPP

#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendAction.h>

#include "CouplingASTConsumer.hpp"

namespace language::cpp
{
class CouplingFrontendAction : public clang::ASTFrontendAction
{
public:
    virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& compiler,
                                                                  llvm::StringRef file);
};

}  // namespace language::cpp


#endif  // STATICCPPCOUPLING_COUPLINGFRONTENDACTION_HPP
