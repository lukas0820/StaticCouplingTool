#ifndef STATICCOUPLINGANALYZER_CONFIGURATIONARGUMENTDATABASE_HPP
#define STATICCOUPLINGANALYZER_CONFIGURATIONARGUMENTDATABASE_HPP

#include <map>
#include <string>
#include <vector>


namespace configuration
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
        std::string defaultValue;
        std::vector<std::string> possibleValues;
    };

    ConfigurationArgumentDatabase();

    ConfigurationArgument getConfigurationArgument(const std::string& optionName) const;

    std::vector<std::string> getAllOptionNames() const;

    void loadArguments(const std::string& databaseName);

private:
    std::map<std::string, ConfigurationArgument> argumentMap;
};

}  // namespace application


#endif  // STATICCOUPLINGANALYZER_CONFIGURATIONARGUMENTDATABASE_HPP
