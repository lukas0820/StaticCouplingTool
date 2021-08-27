#ifndef STATICCOUPLINGANALYZER_JSONPARSER_H
#define STATICCOUPLINGANALYZER_JSONPARSER_H
#include <QJsonDocument>
#include <string>
#include <vector>

namespace application
{
class JSONParser
{
public:
    bool loadJSONDocument(const std::string& absoluteConfigFilePath);

    std::vector<std::string> getOptionValues(const std::string& optionName) const;


private:
    QJsonDocument doc;
    bool docLoaded;
};

}  // namespace application


#endif  // STATICCOUPLINGANALYZER_JSONPARSER_H
