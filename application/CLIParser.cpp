#include "CLIParser.hpp"

namespace application
{
CLIParser::CLIParser(int argc, const char** argv) : argc(argc), argv(argv) {}


CLIParser::Value CLIParser::getOptionValues(const std::string& optionName, const std::string& shortOptionName) const
{
    Value values;

    for (int i = 0; i < argc - 1; i++)
    {
        std::string currentOption(this->argv[i]);
        if (optionNameEqual(currentOption, optionName, shortOptionName))
        {
            values.found = true;
            for (int j = i; j < argc - 1; j++)
            {
                std::string nextValue(argv[j + 1]);
                if (nextValue.substr(0, 1) == "-")
                {
                    break;
                }
                values.valueList.push_back(nextValue);
            }
            break;
        }
    }


    return values;
}

bool CLIParser::optionNameEqual(const std::string& name, const std::string& optionName,
                                const std::string& shortOptionName) const
{
    std::string optionNameToCompare("--");
    optionNameToCompare.append(optionName);

    std::string shortOptionNameToCompare("-");
    shortOptionNameToCompare.append(shortOptionName);

    return optionNameToCompare == name || (!shortOptionName.empty() && shortOptionNameToCompare == name);
}

}  // namespace application