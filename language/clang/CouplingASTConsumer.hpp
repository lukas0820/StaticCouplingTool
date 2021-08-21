#ifndef STATICCPPCOUPLING_COUPLINGASTCONSUMER_HPP
#define STATICCPPCOUPLING_COUPLINGASTCONSUMER_HPP

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/ASTContext.h>

#include "ClangCouplingFinder.hpp"
#include "CouplingVisitor.hpp"


namespace language::cpp
{
class CouplingASTConsumer : public clang::ASTConsumer
{
public:
    explicit CouplingASTConsumer(clang::ASTContext* context, ClangCouplingFinder::ExecutionArguments args);

    virtual void HandleTranslationUnit(clang::ASTContext& Context);

private:
    CouplingVisitor visitor;
};


}  // namespace language::cpp


#endif  // STATICCPPCOUPLING_COUPLINGASTCONSUMER_HPP
