#ifndef STATICCOUPLINGANALYZER_JSONEXPORTER_H
#define STATICCOUPLINGANALYZER_JSONEXPORTER_H

#include <string>

#include "IResultExporter.hpp"

namespace coupling
{
class JSONExporter : public IResultExporter
{
public:
    JSONExporter(const std::string& outputPath);
    void exportCoupling(const CouplingGraph& couplingGraph);

private:
    std::string outputPath;
};
}  // namespace coupling


#endif  // STATICCOUPLINGANALYZER_JSONEXPORTER_H
