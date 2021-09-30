#ifndef STATICCOUPLINGANALYZER_ABSTRACTCOUPLINGAPPLICATION_HPP
#define STATICCOUPLINGANALYZER_ABSTRACTCOUPLINGAPPLICATION_HPP

#include "ICouplingAnalyser.hpp"
#include "ICouplingFinder.hpp"
#include "IResultExporter.hpp"


namespace application
{
class AbstractCouplingApplication
{
public:

    /**
     * @brief Execute
     */
    void execute();

protected:
    /**
     * @brief Constructor.
     * Has to be called by language specific implementation.
     */
    AbstractCouplingApplication(language::ICouplingFinder* couplingFinder, coupling::ICouplingAnalyser* analyser);

    /**
     * @brief The language specific implementations can be initialized here.
     * @return initialization was successful
     */
    virtual bool isReadyForExecution() = 0;

    /**
     * @brief Prints a progress bar to std::cout
     * Can be used as callback for the language specific implementation.
     * @param currentFileNumber number of current file analyzed
     * @param fileCount count of all files
     * @param message message that should be shown for the current file
     */
    virtual void showProgressBar(size_t currentFileNumber, size_t fileCount, const std::string& message);


private:
    void init();


protected:
    std::string projectFilePath;


private:
    language::ICouplingFinder* couplingFinder;
    coupling::ICouplingAnalyser* couplingAnalyser;
    coupling::IResultExporter* resultExporter;
};
}  // namespace application


#endif  // STATICCOUPLINGANALYZER_ABSTRACTCOUPLINGAPPLICATION_HPP
