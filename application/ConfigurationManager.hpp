#ifndef STATICCOUPLINGANALYZER_CONFIGURATIONMANAGER_HPP
#define STATICCOUPLINGANALYZER_CONFIGURATIONMANAGER_HPP

#include <functional>
#include <vector>

#include "CLIParser.hpp"
#include "ConfigurationArgumentDatabase.hpp"
#include "JSONParser.hpp"

namespace application
{
class ConfigurationManager
{
public:
    static void setArguments(int argc, const char** argv);

    static ConfigurationManager* getInstance();

    std::vector<std::string> getOptionValues(const std::string& optionName) const;

    std::string getOptionValue(const std::string& optionName) const;

    bool hasOptionValue(const std::string& optionName) const;


private:
    ConfigurationManager(int argc, const char** argv);

    bool isValidArgument(const std::string& argument,
                         const ConfigurationArgumentDatabase::ConfigurationArgument& configurationArgument) const;

    void showUserInputMessage(const ConfigurationArgumentDatabase::ConfigurationArgument& configurationArgument,
                              const std::string& invalidInput = "") const;

    std::string getValidUserInput(
        const ConfigurationArgumentDatabase::ConfigurationArgument& configurationArgument) const;


private:
    static int argc;
    static const char** argv;
    static bool initialized;


    CLIParser cliParser;
    ConfigurationArgumentDatabase argumentDatabase;
    JSONParser jsonParser;
};

}  // namespace application


#endif  // STATICCOUPLINGANALYZER_CONFIGURATIONMANAGER_HPP
