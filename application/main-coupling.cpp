
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>

#include <iostream>

#include "ClangCouplingApplication.hpp"
#include "ClangCouplingFinder.hpp"
#include "CommandLineExporter.hpp"
#include "ConfigurationManager.hpp"
#include "FileCouplingAnalyser.hpp"
#include "FileUtils.hpp"
#include "JSONExporter.hpp"


using std::string;

using coupling::AbstractCoupling;
using coupling::CommandLineExporter;
using coupling::FileCouplingAnalyser;

using language::cpp::ClangCouplingFinder;


int main(int argc, const char** argv)
{
    application::ConfigurationManager::setArguments(argc, argv);
    std::string language = application::ConfigurationManager::getInstance()->getOptionValue("language");
    application::ClangCouplingApplication app;
    app.execute();

    return 0;
}