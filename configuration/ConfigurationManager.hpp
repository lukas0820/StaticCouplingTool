#ifndef STATICCOUPLINGANALYZER_CONFIGURATIONMANAGER_HPP
#define STATICCOUPLINGANALYZER_CONFIGURATIONMANAGER_HPP

#include <functional>
#include <vector>

#include "CLIParser.hpp"
#include "ConfigurationArgumentDatabase.hpp"
#include "ConfigurationExporter.hpp"
#include "JSONParser.hpp"

namespace configuration
{
class ConfigurationManager
{
public:

    /**
     * @brief Set arguments passed to main function.
     * @param argc argument count
     * @param argv arguments
     */
    static void setArguments(int argc, const char** argv);

    /**
     * @brief Singleton.
     */
    static ConfigurationManager* getInstance();

    /**
     * Get all values fot the given option name
     * @param optionName option Name for that values are requested.
     * @param overrideMandatoryValue if this flag is set, the interactive mode is not started, even if this option is mandatory and missing.
     * @return list of values
     */
    std::vector<std::string> getOptionValues(const std::string& optionName, bool overrideMandatoryValue = false);

    /**
     * Get first value for the given option name
     * @param optionName option Name for that value is requested.
     * @param overrideMandatoryValue if this flag is set, the interactive mode is not started, even if this option is mandatory and missing.
     * @return single value
     */
    std::string getOptionValue(const std::string& optionName, bool overrideMandatoryValue = false);

    /**
     * Checks if the given option is set.
     * @param optionName option name that is requested
     */
    bool hasOptionValue(const std::string& optionName);

    /**
     * @brief Exports all options and its values requested by this class yet.
     */
    void exportConfiguration(const std::string& exportPath);

    /**
     * @brief show all options with description on std::cout
     */
    void showHelp();


private:
    ConfigurationManager(int argc, const char** argv);

    bool isValidArgument(const std::string& argument,
                         const ConfigurationArgumentDatabase::ConfigurationArgument& configurationArgument) const;

    void showUserInputMessage(const ConfigurationArgumentDatabase::ConfigurationArgument& configurationArgument,
                              const std::string& invalidInput = "") const;

    std::string getValidUserInput(
        const ConfigurationArgumentDatabase::ConfigurationArgument& configurationArgument) const;

    void showPossibleValues(const ConfigurationArgumentDatabase::ConfigurationArgument& configurationArgument) const;


private:
    static int argc;
    static const char** argv;
    static bool initialized;


    CLIParser cliParser;
    ConfigurationArgumentDatabase argumentDatabase;
    JSONParser jsonParser;
    ConfigurationExporter configurationExporter;
};

}  // namespace application


#endif  // STATICCOUPLINGANALYZER_CONFIGURATIONMANAGER_HPP
