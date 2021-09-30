#ifndef STATICCOUPLINGANALYZER_JSONEXPORTER_H
#define STATICCOUPLINGANALYZER_JSONEXPORTER_H

#include <string>

#include "IResultExporter.hpp"

namespace coupling
{
class JSONExporter : public IResultExporter
{
public:

    /**
     * @brief Constructor.
     */
    JSONExporter(const std::string& outputPath);

    /**
     * @copydoc IResultExporter::exportCoupling()
     */
    void exportCoupling(const CouplingGraph& couplingGraph);

    /**
     * @brief Get the output path used by this class.
     */
    std::string getPath() const;

private:
    std::string outputPath;
};
}  // namespace coupling


#endif  // STATICCOUPLINGANALYZER_JSONEXPORTER_H
