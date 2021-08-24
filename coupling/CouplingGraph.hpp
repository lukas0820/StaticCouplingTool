

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

    void addCoupling(const std::string& callerName, const std::string& calleeName);
    void addNode(const std::string& nodeName);

    std::vector<std::string> getNodes();

    std::vector<CouplingEdge> getCoupling();


private:
    size_t getIndexOfNode(const std::string& nodeName);
    std::vector<std::string> nodeNames;
    std::vector<std::vector<size_t>> adjacencyMatrix;

    static const size_t NODE_DOES_NOT_EXIST = SIZE_MAX;
};

}  // namespace coupling


#endif  // STATICCOUPLINGANALYZER_COUPLINGGRAPH_H
