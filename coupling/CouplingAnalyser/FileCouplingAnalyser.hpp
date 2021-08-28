#ifndef STATICCOUPLINGANALYZER_FILECOUPLINGANALYSER_H
#define STATICCOUPLINGANALYZER_FILECOUPLINGANALYSER_H

#include <vector>

#include "CouplingGraph.hpp"
#include "ICouplingAnalyser.hpp"


namespace coupling
{
class FileCouplingAnalyser : public ICouplingAnalyser
{
public:
    virtual void handleCoupling(AbstractCoupling* coupling);

    virtual void setResultExporter(IResultExporter* exporter);

    virtual void finish();


private:
    CouplingGraph couplingGraph;
    IResultExporter* resultExporter;
};
}  // namespace coupling


#endif  // STATICCOUPLINGANALYZER_FILECOUPLINGANALYSER_H
