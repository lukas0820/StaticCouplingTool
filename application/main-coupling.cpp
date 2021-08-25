
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>

#include <fstream>
#include <typeinfo>

#include "ClangCouplingFinder.hpp"
#include "CommandLineExporter.hpp"
#include "FileCouplingAnalyser.hpp"

using std::string;

using coupling::AbstractCoupling;
using coupling::CommandLineExporter;
using coupling::FileCouplingAnalyser;

using language::cpp::ClangCouplingFinder;


static llvm::cl::OptionCategory category("test");

int main(int argc, const char** argv)
{
    ClangCouplingFinder couplingFinder;
    ClangCouplingFinder::InitStatus status =
        couplingFinder.init("/home/lukas/Documents/static-coupling/cmake-build-debug");
    std::vector<std::string> fileList = couplingFinder.getCompilationDBFiles();

    CommandLineExporter exporter;

    FileCouplingAnalyser analyser;
    analyser.setResultExporter(&exporter);
    analyser.init(fileList);


    std::function<void(AbstractCoupling*)> analyserCallback = [&analyser](AbstractCoupling* c)
    { analyser.handleCoupling(c); };


    couplingFinder.registerCouplingCallback(coupling::FileCoupling::getCouplingClassTypeId(), analyserCallback);


    if (status == ClangCouplingFinder::InitStatus::OK)
    {
        couplingFinder.execute();
        analyser.finish();
    }

    return 0;
}