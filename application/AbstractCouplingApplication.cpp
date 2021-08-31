
#include "AbstractCouplingApplication.hpp"

#include <chrono>
#include <functional>
#include <iostream>

#include "AbstractCoupling.hpp"
#include "CommandLineExporter.hpp"
#include "ConfigurationManager.hpp"
#include "FileUtils.hpp"
#include "JSONExporter.hpp"

using application::ConfigurationManager;
using coupling::AbstractCoupling;
namespace application
{
AbstractCouplingApplication::AbstractCouplingApplication(language::ICouplingFinder* couplingFinder,
                                                         coupling::ICouplingAnalyser* analyser)
    : couplingFinder(couplingFinder), couplingAnalyser(analyser), resultExporter(nullptr)
{
}

void AbstractCouplingApplication::execute()
{
    ConfigurationManager* configManager = ConfigurationManager::getInstance();


    this->projectFilePath = configManager->getOptionValue("project-path");
    std::cout << "Project path to analyze set to " << this->projectFilePath << std::endl;

    std::function<void(AbstractCoupling*)> analyserCallback = [this](AbstractCoupling* c)
    { this->couplingAnalyser->handleCoupling(c); };

    std::string outputPath = configManager->getOptionValue("output");


    bool hasJsonExporter = !outputPath.empty();
    if (!hasJsonExporter)
    {
        std::cout << "No output path set. Results are output to the command line" << std::endl;
        static coupling::CommandLineExporter clExporter;
        this->resultExporter = &clExporter;
    }
    else
    {
        std::cout << "Output path set to " << outputPath << std::endl;
        static coupling::JSONExporter jsonExporter(outputPath);
        this->resultExporter = &jsonExporter;
    }

    this->couplingAnalyser->setResultExporter(this->resultExporter);

    couplingFinder->registerCouplingCallback(analyserCallback);

    if (isReadyForExecution())
    {
        auto now = std::chrono::system_clock::now().time_since_epoch();
        size_t start_time = std::chrono::duration_cast<std::chrono::seconds>(now).count();

        this->couplingFinder->execute();
        this->couplingAnalyser->finish();


        now = std::chrono::system_clock::now().time_since_epoch();
        size_t end_time = std::chrono::duration_cast<std::chrono::seconds>(now).count();

        if (hasJsonExporter)
        {
            coupling::JSONExporter* jsonExporter = (coupling::JSONExporter*)(this->resultExporter);
            configManager->exportConfiguration(jsonExporter->getPath());
        }

        std::cout << "time: " << end_time - start_time << " seconds" << std::endl;
    }
    else
    {
        std::cout << "Fatal error occured. Please check your configuration and restart." << std::endl;
    }
}


}  // namespace application