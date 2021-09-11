#ifndef STATICCOUPLINGANALYZER_CONFIGURATIONEXPORTER_HPP
#define STATICCOUPLINGANALYZER_CONFIGURATIONEXPORTER_HPP

#include "QJsonObject"

namespace configuration
{
class ConfigurationExporter
{
public:
    void exportConfiguration(const std::string& path);

    void addToExportConfiguration(const std::string& argumentName, const std::vector<std::string>& entrys);

    void addToExportConfiguration(const std::string& argumentName, bool entry);

private:
    QJsonObject rootObject;
};

}  // namespace application


#endif  // STATICCOUPLINGANALYZER_CONFIGURATIONEXPORTER_HPP
