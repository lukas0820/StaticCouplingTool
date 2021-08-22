#include "CouplingVisitor.hpp"

using std::string;

using clang::ASTContext;
using clang::FullSourceLoc;

namespace language
{
namespace cpp
{
CouplingVisitor::CouplingVisitor(ASTContext* Context, ClangCouplingFinder::ExecutionArguments args)
    : context(Context), executionArguments(args)
{
    init();
}

void CouplingVisitor::init()
{
    for (std::string s : this->executionArguments.sourceFileList)
    {
        sourceFiles.push_back(s.substr(0, s.find_last_of(".")));
    }
}

bool CouplingVisitor::isCoupling(const std::string& callee) const
{
    std::string fileNameWithoutExtension = callee.substr(0, callee.find_last_of("."));
    return std::find(this->sourceFiles.begin(), this->sourceFiles.end(), fileNameWithoutExtension) !=
           this->sourceFiles.end();
}

bool CouplingVisitor::VisitCallExpr(clang::CallExpr* call)
{
    clang::FullSourceLoc FullLocation = context->getFullLoc(call->getBeginLoc());
    clang::FileID fileID = FullLocation.getFileID();
    unsigned int thisFileID = fileID.getHashValue();
    if (thisFileID == 1)
    {
        static unsigned int count = 0;
        count++;
        clang::FunctionDecl* func_decl;

        if (call->getDirectCallee())
        {
            func_decl = call->getDirectCallee();
            clang::FullSourceLoc callerLocation = context->getFullLoc(call->getBeginLoc());
            clang::FullSourceLoc declLocation = context->getFullLoc(func_decl->getEndLoc());

            if (declLocation.getFileEntry() && callerLocation.getFileEntry())
            {
                std::string funcCall = func_decl->getNameInfo().getName().getAsString();

                if (isCoupling(declLocation.getFileEntry()->getName().str()))
                {
                    coupling::FileCoupling coupling(callerLocation.getFileEntry()->getName().str(),
                                                    declLocation.getFileEntry()->getName().str(), funcCall);

                    this->executionArguments.couplingCallback(&coupling);
                }

                //                llvm::outs() << funcCall << "\n";
                //                llvm::outs() << callerLocation.getFileEntry()->getName() << " -> "
                //                             << declLocation.getFileEntry()->getName() << " " << count << "\n";
            }
        }
    }

    return true;
}


}  // namespace cpp
}  // namespace language
