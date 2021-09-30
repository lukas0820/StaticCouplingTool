

#ifndef STATICCOUPLINGANALYZER_COUPLINGGRAPH_H
#define STATICCOUPLINGANALYZER_COUPLINGGRAPH_H

#include <string>
#include <vector>

namespace coupling
{
class CouplingGraph
{
public:
    struct CouplingEdge
    {
        std::string caller;
        std::string callee;
        size_t couplingCount;
    };

    /**
     * @brief add an edge to this graph.
     * If the graph does not contain the nodes, they will be added.
     */
    void addCoupling(const std::string& callerName, const std::string& calleeName);

    /**
     * add a node to this graph.
     */
    void addNode(const std::string& nodeName);

    /**
     * @brief get all Nodes.
     * @return List of all nodes
     */
    std::vector<std::string> getNodes() const;

    /**
     * @brief Get all edges.
     * @return List of all edges.
     */
    std::vector<CouplingEdge> getCoupling() const;


private:
    size_t getIndexOfNode(const std::string& nodeName);
    std::vector<std::string> nodeNames;
    std::vector<std::vector<size_t>> adjacencyMatrix;

    static const size_t NODE_DOES_NOT_EXIST = SIZE_MAX;
};

}  // namespace coupling


#endif  // STATICCOUPLINGANALYZER_COUPLINGGRAPH_H
