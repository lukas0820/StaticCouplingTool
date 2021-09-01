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
    AbstractCouplingApplication(language::ICouplingFinder* couplingFinder, coupling::ICouplingAnalyser* analyser);

    void execute();

protected:
    virtual bool isReadyForExecution() = 0;

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
