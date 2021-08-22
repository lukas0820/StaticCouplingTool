

#ifndef STATICCOUPLINGANALYZER_COUPLINGGRAPH_H
#define STATICCOUPLINGANALYZER_COUPLINGGRAPH_H

#include <string>
#include <vector>

namespace coupling
{
class CouplingGraph
{
public:
    void addCoupling(const std::string& callerName, const std::string& calleeName);

private:
    size_t getIndexOfNode(const std::string& nodeName);


    void addNode(const std::string& nodeName);
    std::vector<std::string> nodeNames;
    std::vector<std::vector<size_t>> adjacencyMatrix;
};

}  // namespace coupling


#endif  // STATICCOUPLINGANALYZER_COUPLINGGRAPH_H
