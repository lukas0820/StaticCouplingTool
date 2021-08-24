#ifndef STATICCOUPLINGANALYZER_ICOUPLINGANALYSER_H
#define STATICCOUPLINGANALYZER_ICOUPLINGANALYSER_H

#include "AbstractCoupling.hpp"

namespace coupling
{
class ICouplingAnalyser
{
    virtual void handleCoupling(AbstractCoupling* coupling) = 0;
};
}  // namespace coupling
#endif  // STATICCOUPLINGANALYZER_ICOUPLINGANALYSER_H
