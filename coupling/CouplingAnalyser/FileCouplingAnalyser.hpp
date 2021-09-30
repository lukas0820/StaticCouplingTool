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

    /**
     * @copydoc ICouplingAnalyser::handleCoupling()
     */
    virtual void handleCoupling(shared::AbstractCoupling* coupling);

    /**
     * @copydoc ICouplingAnalyser::setResultExporter()
     */
    virtual void setResultExporter(IResultExporter* exporter);

    /**
     * @copydoc ICouplingAnalyser::finish()
     */
    virtual void finish();


private:
    CouplingGraph couplingGraph;
    IResultExporter* resultExporter;
};
}  // namespace coupling


#endif  // STATICCOUPLINGANALYZER_FILECOUPLINGANALYSER_H
