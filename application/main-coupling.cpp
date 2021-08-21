#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>

#include <QDebug>
#include <QDirIterator>
#include <fstream>

#include "ClangCouplingFinder.hpp"
#include "CouplingFrontendAction.hpp"

using std::string;

static llvm::cl::OptionCategory category("test");

int main(int argc, const char** argv)
{
    language::cpp::ClangCouplingFinder couplingFinder;
    language::cpp::ClangCouplingFinder::InitStatus status = couplingFinder.init("/home/lukas/Desktop/linux-5.13.8");
    if (status == language::cpp::ClangCouplingFinder::InitStatus::OK)
    {
        couplingFinder.execute();
    }
    
    return 0;
}