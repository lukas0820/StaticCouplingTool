#ifndef STATICCOUPLINGANALYZER_TYPESOURCEFINDER_H
#define STATICCOUPLINGANALYZER_TYPESOURCEFINDER_H

#include <clang/AST/ASTContext.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/FileEntry.h>

#include <string>
namespace language::cpp
{
class TypeSourceFinder : public clang::RecursiveASTVisitor<TypeSourceFinder>
{
public:
    explicit TypeSourceFinder(clang::ASTContext* Context);

    std::string getDeclTypePath(clang::QualType type);

    bool VisitCXXRecordDecl(clang::CXXRecordDecl* call);


private:
    clang::QualType type;
    std::string filePath;
    clang::ASTContext* context;
};

}  // namespace language::cpp


#endif  // STATICCOUPLINGANALYZER_TYPESOURCEFINDER_H
