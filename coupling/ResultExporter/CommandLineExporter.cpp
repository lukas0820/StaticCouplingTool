#include "CommandLineExporter.hpp"

#include <iostream>

namespace coupling
{
void CommandLineExporter::exportCoupling(const CouplingGraph& couplingGraph)
{
    auto coupling = couplingGraph.getCoupling();

    std::cout << "[info] ---------------------- results ----------------------" << std::endl;
    for (auto node : couplingGraph.getNodes())
    {
        std::cout << "[node] " << node << std::endl;
    }

    for (CouplingGraph::CouplingEdge edge : coupling)
    {
        std::cout << "[edge] " << edge.caller << " -> " << edge.callee << " : " << edge.couplingCount << std::endl;
    }
    std::cout << "[info] -----------------------------------------------------" << std::endl;
}
}  // namespace coupling