#include "ConfigurationManager.hpp"

#include <iostream>

#include "ContainerUtils.hpp"

using utils::ContainerUtils;

namespace application
{
int ConfigurationManager::argc = 0;
const char** ConfigurationManager::argv;
bool ConfigurationManager::initialized = false;

void ConfigurationManager::setArguments(int argc, const char** argv)
{
    ConfigurationManager::argc = argc;
    ConfigurationManager::argv = argv;
    ConfigurationManager::initialized = true;
}

ConfigurationManager* ConfigurationManager::getInstance()
{
    ConfigurationManager* returnValue = nullptr;
    if (ConfigurationManager::initialized)
    {
        static ConfigurationManager instance(ConfigurationManager::argc, ConfigurationManager::argv);
        returnValue = &instance;
    }

    return returnValue;
}
ConfigurationManager::ConfigurationManager(int argc, const char** argv) : cliParser(argc, argv)
{
    std::string configPath = getOptionValue("config-path");
    if (!configPath.empty())
    {
        if (this->jsonParser.loadJSONDocument(configPath))
        {
            std::cout << "loaded config file from " << configPath << std::endl;
        }
        else
        {
            std::cout << "Failed to load config file. File does not exist" << std::endl;
        }
    }
}

std::vector<std::string> ConfigurationManager::getOptionValues(const std::string& optionName)
{
    std::vector<std::string> valueList;

    auto configurationArgument = this->argumentDatabase.getConfigurationArgument(optionName);


    auto valuesCli =
        this->cliParser.getOptionValues(configurationArgument.optionName, configurationArgument.shortOptionName);

    valueList = valuesCli.valueList;

    auto valuesJson = this->jsonParser.getOptionValues(optionName);

    if (!valuesJson.empty())
    {
        for (auto i : valuesJson)
        {
            if (!ContainerUtils::isInVector<std::string>(valueList, i))
            {
                valueList.push_back(i);
            }
        }
    }


    std::vector<std::string> returnList;
    for (auto s : valueList)
    {
        if (isValidArgument(s, configurationArgument))
        {
            returnList.push_back(s);
        }
        else
        {
            std::cout << s << " is invalid for option " << configurationArgument.optionName << "." << std::endl;
        }
    }


    if (returnList.empty() && configurationArgument.mandatory)
    {
        showUserInputMessage(configurationArgument);
        std::string input = getValidUserInput(configurationArgument);
        returnList.push_back(input);
    }

    if (optionName == "language")
    {
        this->argumentDatabase.loadArguments(returnList[0]);
    }

    if (configurationArgument.optionName != "config-path")
    {
        this->configurationExporter.addToExportConfiguration(configurationArgument.optionName, returnList);
    }

    return returnList;
}

std::string ConfigurationManager::getOptionValue(const std::string& optionName)
{
    auto values = getOptionValues(optionName);
    return (!values.empty()) ? values[0] : "";
}

bool ConfigurationManager::hasOptionValue(const std::string& optionName)
{
    bool found = false;
    auto configurationArgument = this->argumentDatabase.getConfigurationArgument(optionName);
    auto valuesCli =
        this->cliParser.getOptionValues(configurationArgument.optionName, configurationArgument.shortOptionName);

    found = valuesCli.found;

    if (!found)
    {
        auto valuesJson = jsonParser.getOptionValues(configurationArgument.optionName);
        if (!valuesJson.empty())
        {
            found = valuesJson[0] == "true";
        }
    }

    this->configurationExporter.addToExportConfiguration(configurationArgument.optionName, found);

    return found;
}

void ConfigurationManager::exportConfiguration(const std::string& exportPath)
{
    this->configurationExporter.exportConfiguration(exportPath);
}

bool ConfigurationManager::isValidArgument(
    const std::string& argument,
    const ConfigurationArgumentDatabase::ConfigurationArgument& configurationArgument) const
{
    bool returnValue = true;
    if (!configurationArgument.possibleValues.empty())
    {
        returnValue = ContainerUtils::isInVector<std::string>(configurationArgument.possibleValues, argument);
    }

    return returnValue;
}

void ConfigurationManager::showUserInputMessage(
    const ConfigurationArgumentDatabase::ConfigurationArgument& configurationArgument,
    const std::string& invalidInput) const
{
    if (!invalidInput.empty())
    {
        std::cout << invalidInput << " is invalid for option " << configurationArgument.optionName << ". ";
    }

    std::cout << "Please enter " << configurationArgument.description;

    int possibleValueCount = configurationArgument.possibleValues.size();
    if (possibleValueCount > 0)
    {
        std::cout << ". Possible values are [";
        for (int i = 0; i < possibleValueCount; i++)

        {
            std::cout << configurationArgument.possibleValues[i];
            if (i + 1 < possibleValueCount)
            {
                std::cout << ", ";
            }
        }

        std::cout << "] :" << std::endl;
    }
    else
    {
        std::cout << ": " << std::endl;
    }
}

std::string ConfigurationManager::getValidUserInput(
    const ConfigurationArgumentDatabase::ConfigurationArgument& configurationArgument) const
{
    std::string input;
    std::cin >> input;

    while (!isValidArgument(input, configurationArgument))
    {
        showUserInputMessage(configurationArgument, input);
        input = "";
        std::cin >> input;
    }

    return input;
}
}  // namespace application