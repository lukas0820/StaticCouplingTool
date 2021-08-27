#ifndef STATICCOUPLINGANALYZER_CLIPARSER_H
#define STATICCOUPLINGANALYZER_CLIPARSER_H

#include <QCommandLineParser>
#include <map>
#include <string>
#include <vector>

namespace application
{
class CLIParser
{
public:
    struct Value
    {
        std::vector<std::string> valueList;
        bool found = false;
    };

    CLIParser(int argc, const char** argv);
    
    Value getOptionValues(const std::string& optionName, const std::string& shortOptionName = "") const;

private:
    bool optionNameEqual(const std::string& name, const std::string& optionName,
                         const std::string& shortOptionName) const;

private:
    int argc;
    const char** argv;
};
}  // namespace application


#endif  // STATICCOUPLINGANALYZER_CLIPARSER_H
