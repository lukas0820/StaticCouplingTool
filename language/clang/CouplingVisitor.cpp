#include "CouplingVisitor.hpp"

using std::string;

using clang::ASTContext;
using clang::FullSourceLoc;

namespace language
{
namespace cpp
{
CouplingVisitor::CouplingVisitor(ASTContext* Context) : context(Context) {}


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
