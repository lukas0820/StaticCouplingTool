
#include <clang/Tooling/Tooling.h>
#include "ClangCouplingApplication.hpp"
#include "ClangCouplingFinder.hpp"
#include "CommandLineExporter.hpp"
#include "ConfigurationManager.hpp"
#include "FileCouplingAnalyser.hpp"
#include "FileUtils.hpp"


using std::string;

using shared::AbstractCoupling;
using coupling::CommandLineExporter;
using coupling::FileCouplingAnalyser;

using language::cpp::ClangCouplingFinder;


int main(int argc, const char** argv)
{
    configuration::ConfigurationManager::setArguments(argc, argv);
    configuration::ConfigurationManager* configurationManager = configuration::ConfigurationManager::getInstance();

    if (configurationManager->hasOptionValue("help"))
    {
        configurationManager->showHelp();
    }
    else
    {
        std::string language = configurationManager->getOptionValue("language");
        application::AbstractCouplingApplication* app = nullptr;
        if(language == "cpp")
        {
            static application::ClangCouplingApplication clangApp;
            app = &clangApp;

        }
        else{

            //Implementations for other languages can be added here.
        }

        if(app)
        {
            app->execute();
        }

    }


    return 0;
}