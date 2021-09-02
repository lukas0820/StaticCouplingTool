#include "TypeSourceFinder.h"

#include <iostream>

namespace language::cpp
{
TypeSourceFinder::TypeSourceFinder(clang::ASTContext* Context) : context(Context) {}

bool TypeSourceFinder::VisitCXXRecordDecl(clang::CXXRecordDecl* call)
{
    bool notFound = true;
    std::cout << call->getQualifiedNameAsString() << std::endl;
    
    if (call->getNameAsString() == this->type.getAsString())
    {
        std::string fileName = "";
        clang::FullSourceLoc location = this->context->getFullLoc(call->getBeginLoc());
        if (location.getFileEntry())
        {
            fileName = location.getFileEntry()->getName().str();
            this->filePath = fileName;
            notFound = false;
        }
    }

    return notFound;
}

std::string TypeSourceFinder::getDeclTypePath(clang::QualType type)
{
    std::string returnValue;
    this->type = type;
    if (!this->TraverseDecl(this->context->getTranslationUnitDecl()))
    {
        returnValue = this->filePath;
    };
    return returnValue;
}
}  // namespace language::cpp