
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/CommandLine.h>

#include "ClangCouplingApplication.hpp"
#include "ClangCouplingFinder.hpp"
#include "CommandLineExporter.hpp"
#include "ConfigurationManager.hpp"
#include "FileCouplingAnalyser.hpp"
#include "FileUtils.hpp"


using std::string;

using coupling::AbstractCoupling;
using coupling::CommandLineExporter;
using coupling::FileCouplingAnalyser;

using language::cpp::ClangCouplingFinder;


int main(int argc, const char** argv)
{
    application::ConfigurationManager::setArguments(argc, argv);
    application::ConfigurationManager* configurationManager = application::ConfigurationManager::getInstance();

    if (configurationManager->hasOptionValue("help"))
    {
        configurationManager->showHelp();
    }
    else
    {
        std::string language = configurationManager->getOptionValue("language");
        application::AbstractCouplingApplication* app = nullptr;
        if(language == "clang")
        {
            static application::ClangCouplingApplication clangApp;
            app = &clangApp;

        }

        if(app)
        {
            app->execute();
        }

    }


    return 0;
}