#ifndef STATICCOUPLINGANALYZER_FILECOUPLINGANALYSER_H
#define STATICCOUPLINGANALYZER_FILECOUPLINGANALYSER_H

#include <vector>

#include "CouplingGraph.hpp"
#include "ICouplingAnalyser.hpp"


namespace coupling
{
class FileCouplingAnalyser : public ICouplingAnalyser
{
public:
    virtual void handleCoupling(AbstractCoupling* coupling);

    void init(const std::vector<std::string>& fileList);


private:
    CouplingGraph couplingGraph;
};
}  // namespace coupling


#endif  // STATICCOUPLINGANALYZER_FILECOUPLINGANALYSER_H
