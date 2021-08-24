#ifndef STATICCOUPLINGANALYZER_IRESULTEXPORTER_H
#define STATICCOUPLINGANALYZER_IRESULTEXPORTER_H

#include "CouplingGraph.hpp"

namespace coupling
{
class IResultExporter
{
    virtual void exportCoupling(const CouplingGraph& couplingGraph) = 0;
};

}  // namespace coupling


#endif  // STATICCOUPLINGANALYZER_IRESULTEXPORTER_H
