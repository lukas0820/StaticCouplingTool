#ifndef STATICCOUPLINGANALYZER_ABSTRACTCOUPLINGAPPLICATION_H
#define STATICCOUPLINGANALYZER_ABSTRACTCOUPLINGAPPLICATION_H

#include "ICouplingAnalyser.hpp"
#include "ICouplingFinder.hpp"
#include "IResultExporter.hpp"


namespace application
{
class AbstractCouplingApplication
{
public:
    AbstractCouplingApplication(language::ICouplingFinder* couplingFinder, coupling::ICouplingAnalyser* analyser,
                                coupling::IResultExporter* exporter);

    void execute();

protected:
    virtual bool isReadyForExecution() = 0;


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


#endif  // STATICCOUPLINGANALYZER_ABSTRACTCOUPLINGAPPLICATION_H
