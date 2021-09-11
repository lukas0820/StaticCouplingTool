
#include "AbstractCouplingApplication.hpp"

#include <chrono>
#include <functional>
#include <iostream>

#include "AbstractCoupling.hpp"
#include "CommandLineExporter.hpp"
#include "ConfigurationManager.hpp"
#include "FileUtils.hpp"
#include "JSONExporter.hpp"

using configuration::ConfigurationManager;
using shared::AbstractCoupling;
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

    std::function<void(AbstractCoupling*)> analyserCallback = [this](AbstractCoupling* c)
    { this->couplingAnalyser->handleCoupling(c); };

    language::ProgressCallback progressCallback = [this](size_t i, size_t j, const std::string& s)
    { this->showProgressBar(i, j, s); };


    std::string outputPath = configManager->getOptionValue("output");


    bool hasJsonExporter = !outputPath.empty();
    if (!hasJsonExporter)
    {
        std::cout << "[warn] No output path set. Results are output to the command line" << std::endl;
        static coupling::CommandLineExporter clExporter;
        this->resultExporter = &clExporter;
    }
    else
    {
        static coupling::JSONExporter jsonExporter(outputPath);
        this->resultExporter = &jsonExporter;
    }

    this->couplingAnalyser->setResultExporter(this->resultExporter);

    this->couplingFinder->registerCouplingCallback(analyserCallback);
    this->couplingFinder->registerProgressCallback(progressCallback);

    if (isReadyForExecution())
    {
        auto now = std::chrono::system_clock::now().time_since_epoch();
        size_t start_time = std::chrono::duration_cast<std::chrono::seconds>(now).count();

        std::cout << "[info] Starting analyser" << std::endl;

        this->couplingFinder->execute();
        std::cout << std::endl;

        this->couplingAnalyser->finish();

        if (hasJsonExporter)
        {
            coupling::JSONExporter* jsonExporter = (coupling::JSONExporter*)(this->resultExporter);
            configManager->exportConfiguration(jsonExporter->getPath());
        }

        now = std::chrono::system_clock::now().time_since_epoch();
        size_t end_time = std::chrono::duration_cast<std::chrono::seconds>(now).count();

        std::cout << "[info] finished after " << end_time - start_time << " seconds" << std::endl;
    }
    else
    {
        std::cout << "Fatal error occured. Please check your configuration and restart." << std::endl;
    }
}

void AbstractCouplingApplication::showProgressBar(size_t currentFileNumber, size_t fileCount,
                                                  const std::string& message)
{
    float progress = static_cast<float>(currentFileNumber) / static_cast<float>(fileCount);

    int barWidth = 40;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < pos)
            std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << "% (" << currentFileNumber << " of " << fileCount << " files)"
              << "\r";
    std::cout.flush();
}


}  // namespace application