#ifndef STATICCOUPLINGANALYZER_IRESULTEXPORTER_H
#define STATICCOUPLINGANALYZER_IRESULTEXPORTER_H

#include "CouplingGraph.hpp"

namespace coupling
{
class IResultExporter
{
public:

    /**
     * @brief exports the given coupling graph
     */
    virtual void exportCoupling(const CouplingGraph& couplingGraph) = 0;
};

}  // namespace coupling


#endif  // STATICCOUPLINGANALYZER_IRESULTEXPORTER_H
