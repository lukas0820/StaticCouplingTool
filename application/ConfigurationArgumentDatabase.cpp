#include "ConfigurationArgumentDatabase.hpp"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace application
{
ConfigurationArgumentDatabase::ConfigurationArgumentDatabase()
{
    loadArguments("base");
}

ConfigurationArgumentDatabase::ConfigurationArgument ConfigurationArgumentDatabase::getConfigurationArgument(
    const std::string& optionName) const
{
    return this->argumentMap.at(optionName);
}

std::vector<std::string> ConfigurationArgumentDatabase::getAllOptionNames() const
{
    std::vector<std::string> keys;
    for (auto i : this->argumentMap)
    {
        keys.push_back(i.first);
    }
    return keys;
}

void ConfigurationArgumentDatabase::loadArguments(const std::string& databaseName)
{
    QFile file;

    file.setFileName(PROJECT_ROOT_PATH);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    auto val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val);
    QJsonArray array = doc.object().value(QString::fromStdString(databaseName)).toArray();

    foreach (const QJsonValue& value, array)
    {
        QJsonObject obj = value.toObject();
        std::string optionName = obj["optionName"].toString().toStdString();

        ConfigurationArgument argument;
        argument.optionName = optionName;
        argument.shortOptionName = obj["shortOptionName"].toString().toStdString();
        argument.mandatory = obj["mandatory"].toBool();
        argument.description = obj["description"].toString().toStdString();
        argument.defaultValue = obj["default"].toString().toStdString();

        for (auto i : obj["possibleValues"].toArray())
        {
            argument.possibleValues.push_back(i.toString().toStdString());
        }


        this->argumentMap[optionName] = argument;
    }
}
}  // namespace application
