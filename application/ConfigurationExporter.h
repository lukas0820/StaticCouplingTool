#ifndef STATICCOUPLINGANALYZER_CONFIGURATIONEXPORTER_H
#define STATICCOUPLINGANALYZER_CONFIGURATIONEXPORTER_H

#include "QJsonObject"

namespace application
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


#endif  // STATICCOUPLINGANALYZER_CONFIGURATIONEXPORTER_H
