
#include "AbstractCouplingApplication.hpp"

#include <chrono>
#include <functional>
#include <iostream>

#include "AbstractCoupling.hpp"
#include "ConfigurationManager.hpp"
#include "FileUtils.hpp"

using application::ConfigurationManager;
using coupling::AbstractCoupling;
namespace application
{
AbstractCouplingApplication::AbstractCouplingApplication(language::ICouplingFinder* couplingFinder,
                                                         coupling::ICouplingAnalyser* analyser,
                                                         coupling::IResultExporter* exporter)
    : couplingFinder(couplingFinder), couplingAnalyser(analyser), resultExporter(exporter)
{
}

void AbstractCouplingApplication::execute()
{
    ConfigurationManager* configManager = ConfigurationManager::getInstance();


    this->projectFilePath = configManager->getOptionValue("project-path");

    std::function<void(AbstractCoupling*)> analyserCallback = [this](AbstractCoupling* c)
    { this->couplingAnalyser->handleCoupling(c); };

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

        std::cout << "time: " << end_time - start_time << " seconds" << std::endl;
    }
    else
    {
        std::cout << "Fatal error occured. Please check your configuration and restart." << std::endl;
    }
}


}  // namespace application