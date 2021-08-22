#ifndef STATICCPPCOUPLING_COUPLINGVISITOR_HPP
#define STATICCPPCOUPLING_COUPLINGVISITOR_HPP

#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/FileEntry.h>

#include "ClangCouplingFinder.hpp"


namespace language::cpp
{
class CouplingVisitor : public clang::RecursiveASTVisitor<CouplingVisitor>
{
public:
    explicit CouplingVisitor(clang::ASTContext* Context, ClangCouplingFinder::ExecutionArguments executionArguments);

    void init();

    bool VisitCallExpr(clang::CallExpr* call);

    bool VisitCXXConstructExpr(clang::CXXConstructExpr* expr);


    bool isCoupling(const std::string& callee) const;

private:
    std::string getStatementFileName(clang::Stmt* stmt);

    clang::ASTContext* context;
    std::vector<std::string> sourceFiles;
    ClangCouplingFinder::ExecutionArguments executionArguments;
};

}  // namespace language::cpp


#endif  // STATICCPPCOUPLING_COUPLINGVISITOR_HPP
