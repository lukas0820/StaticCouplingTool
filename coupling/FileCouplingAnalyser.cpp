#include "FileCouplingAnalyser.hpp"

#include <iostream>

namespace coupling
{
void FileCouplingAnalyser::handleCoupling(AbstractCoupling* coupling)
{
    if (coupling)
    {
        this->couplingGraph.addCoupling(coupling->getCaller(), coupling->getCallee());
    }

    coupling::FileCoupling* fileCoupling = (coupling::FileCoupling*)coupling;
    std::cout << fileCoupling->getFunctionName() << " : " << coupling->getCaller() << " -> " << coupling->getCallee()
              << std::endl;
}

void FileCouplingAnalyser::init(const std::vector<std::string>& fileList)
{
    for (auto s : fileList)
    {
        this->couplingGraph.addNode(s);
    }
}

}  // namespace coupling