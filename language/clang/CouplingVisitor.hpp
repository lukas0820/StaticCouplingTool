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
    
    bool VisitCXXConstructExpr(clang::CXXConstructExpr* expr);

    bool VisitDeclRefExpr(clang::DeclRefExpr* expr);

    bool VisitCXXRecordDecl(clang::CXXRecordDecl* call);


private:
    bool isCoupling(const clang::SourceLocation&, const clang::SourceLocation& callee) const;

    bool isInCurrentFile(const clang::SourceLocation& sourceLocation) const;

    std::string getSourceLocationFileName(const clang::SourceLocation& sourceLocation) const;

    clang::ASTContext* context;
    std::vector<std::string> sourceFiles;
    ClangCouplingFinder::ExecutionArguments executionArguments;
};

}  // namespace language::cpp


#endif  // STATICCPPCOUPLING_COUPLINGVISITOR_HPP
