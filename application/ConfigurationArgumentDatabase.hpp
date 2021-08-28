#ifndef STATICCOUPLINGANALYZER_CONFIGURATIONARGUMENTDATABASE_HPP
#define STATICCOUPLINGANALYZER_CONFIGURATIONARGUMENTDATABASE_HPP

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
        std::string defaultValue;
        std::vector<std::string> possibleValues;
    };

    ConfigurationArgumentDatabase();

    ConfigurationArgument getConfigurationArgument(const std::string& optionName) const;

    std::vector<std::string> getAllOptionNames() const;


private:
    void loadArguments();
    std::map<std::string, ConfigurationArgument> argumentMap;
};

}  // namespace application


#endif  // STATICCOUPLINGANALYZER_CONFIGURATIONARGUMENTDATABASE_HPP
