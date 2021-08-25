#ifndef STATICCOUPLINGANALYZER_COMMANDLINEEXPORTER_H
#define STATICCOUPLINGANALYZER_COMMANDLINEEXPORTER_H

#include "IResultExporter.hpp"

namespace coupling
{
class CommandLineExporter : public IResultExporter
{
    virtual void exportCoupling(const CouplingGraph& couplingGraph);
};
}  // namespace coupling


#endif  // STATICCOUPLINGANALYZER_COMMANDLINEEXPORTER_H
