#ifndef STATICCPPCOUPLING_COUPLINGVISITOR_HPP
#define STATICCPPCOUPLING_COUPLINGVISITOR_HPP

#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/FileEntry.h>


namespace language::cpp
{
class CouplingVisitor : public clang::RecursiveASTVisitor<CouplingVisitor>
{
public:
    explicit CouplingVisitor(clang::ASTContext* Context);

    clang::ASTContext* context;

    bool VisitCallExpr(clang::CallExpr* call);
};

}  // namespace language::cpp


#endif  // STATICCPPCOUPLING_COUPLINGVISITOR_HPP
