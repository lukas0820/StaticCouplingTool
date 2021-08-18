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
    QDirIterator it("/home/lukas/Desktop/linux-5.13.8", QDirIterator::Subdirectories);

    std::vector<std::string> files;
    while (it.hasNext())
    {
        QString fileName = it.next();
        if (fileName.endsWith(".hpp") || fileName.endsWith(".cpp") || fileName.endsWith(".c") ||
            fileName.endsWith(".h"))
        {
            files.push_back(fileName.toStdString());
        }
    }


    ClangCouplingFinder couplingFinder("/home/lukas/Desktop/linux-5.13.8", files);
    couplingFinder.execute();


    return 0;
}