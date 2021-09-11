#include "FileCouplingAnalyser.hpp"

#include <iostream>

namespace coupling
{
void FileCouplingAnalyser::handleCoupling(shared::AbstractCoupling* coupling)
{
    if (coupling)
    {
        this->couplingGraph.addCoupling(coupling->getCaller(), coupling->getCallee());
    }

    //    coupling::FileCoupling* fileCoupling = (coupling::FileCoupling*)coupling;
    //    std::cout << fileCoupling->getFunctionName() << " : " << coupling->getCaller() << " -> " <<
    //    coupling->getCallee()
    //              << std::endl;
}

void FileCouplingAnalyser::setResultExporter(IResultExporter* exporter)
{
    this->resultExporter = exporter;
}

void FileCouplingAnalyser::finish()
{
    if (this->resultExporter)
    {
        this->resultExporter->exportCoupling(this->couplingGraph);
    }
}


}  // namespace coupling