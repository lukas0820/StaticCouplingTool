#ifndef STATICCOUPLINGANALYZER_ICOUPLINGANALYSER_H
#define STATICCOUPLINGANALYZER_ICOUPLINGANALYSER_H

#include "AbstractCoupling.hpp"
#include "IResultExporter.hpp"

namespace coupling
{
class ICouplingAnalyser
{
public:

    /**
     * @brief Adds the given coupling object to coupling graph.
     * @param coupling coupling object that should be added to the graph
     */
    virtual void handleCoupling(shared::AbstractCoupling* coupling) = 0;

    /**
     * @brief Set a result exporter that is used after finish() is called.
     * @param exporter
     */
    virtual void setResultExporter(IResultExporter* exporter) = 0;

    /**
     * @brief Starts result exporter.
     */
    virtual void finish() = 0;
};
}  // namespace coupling
#endif  // STATICCOUPLINGANALYZER_ICOUPLINGANALYSER_H
