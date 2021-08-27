#ifndef STATICCOUPLINGANALYZER_CONFIGURATIONARGUMENTDATABASE_H
#define STATICCOUPLINGANALYZER_CONFIGURATIONARGUMENTDATABASE_H

#include <map>
#include <string>
#include <vector>


namespace application
{
class ConfigurationArgumentDatabase
{

public:
    struct ConfigurationArgument
    {
        std::string optionName;
        std::string shortOptionName;
        bool mandatory;
        std::string description;
    };

    ConfigurationArgumentDatabase();

    ConfigurationArgument getConfigurationArgument(const std::string& optionName) const;

    std::vector<std::string> getAllOptionNames() const;


private:
    void loadArguments();
    std::map<std::string, ConfigurationArgument> argumentMap;
};

}  // namespace application


#endif  // STATICCOUPLINGANALYZER_CONFIGURATIONARGUMENTDATABASE_H
