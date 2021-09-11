#ifndef STATICCOUPLINGANALYZER_ICOUPLINGANALYSER_H
#define STATICCOUPLINGANALYZER_ICOUPLINGANALYSER_H

#include "AbstractCoupling.hpp"
#include "IResultExporter.hpp"

namespace coupling
{
class ICouplingAnalyser
{
public:
    virtual void handleCoupling(shared::AbstractCoupling* coupling) = 0;

    virtual void setResultExporter(IResultExporter* exporter) = 0;

    virtual void finish() = 0;
};
}  // namespace coupling
#endif  // STATICCOUPLINGANALYZER_ICOUPLINGANALYSER_H
