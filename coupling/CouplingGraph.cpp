

#include "CouplingGraph.hpp"

#include <algorithm>

namespace coupling
{
void CouplingGraph::addCoupling(const std::string& callerName, const std::string& calleeName)
{
    size_t i = getIndexOfNode(callerName);
    if (i == NODE_DOES_NOT_EXIST)
    {
        addNode(callerName);
        i = getIndexOfNode(callerName);
    }

    size_t j = getIndexOfNode(calleeName);
    if (j == NODE_DOES_NOT_EXIST)
    {
        addNode(calleeName);
        j = getIndexOfNode(calleeName);
    }

    this->adjacencyMatrix[i][j]++;
}

std::vector<std::string> CouplingGraph::getNodes()
{
    return this->nodeNames;
}

std::vector<CouplingGraph::CouplingEdge> CouplingGraph::getCoupling()
{
    std::vector<CouplingEdge> edges;
    for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
    {
        auto row = this->adjacencyMatrix[i];
        std::string callerName = this->nodeNames[i];
        for (size_t j = 0; j < row.size(); j++)
        {
            size_t couplingCount = row[j];
            if (couplingCount > 0)
            {
                CouplingEdge edge;
                edge.caller = callerName;
                edge.callee = this->nodeNames[j];
                edge.couplingCount = couplingCount;
                edges.push_back(edge);
            }
        }
    }

    return edges;
}
size_t CouplingGraph::getIndexOfNode(const std::string& nodeName)
{
    size_t index = NODE_DOES_NOT_EXIST;
    auto it = std::find(this->nodeNames.begin(), this->nodeNames.end(), nodeName);
    if (it != this->nodeNames.end())
    {
        index = it - this->nodeNames.begin();
    }

    return index;
}

void CouplingGraph::addNode(const std::string& nodeName)
{
    this->nodeNames.push_back(nodeName);

    std::vector<size_t> newLine = {0};
    for (size_t i = 0; i < this->adjacencyMatrix.size(); i++)
    {
        this->adjacencyMatrix[i].push_back(0);
        newLine.push_back(0);
    }
    this->adjacencyMatrix.push_back(newLine);
}
}  // namespace coupling
