#include "CommandLineExporter.hpp"

#include <iostream>

namespace coupling
{
void CommandLineExporter::exportCoupling(const CouplingGraph& couplingGraph)
{
    auto coupling = couplingGraph.getCoupling();
    for (CouplingGraph::CouplingEdge edge : coupling)
    {
        std::cout << "CommandLineExporter" << edge.caller << " -> " << edge.callee << " : " << edge.couplingCount
                  << std::endl;
    }
}
}  // namespace coupling