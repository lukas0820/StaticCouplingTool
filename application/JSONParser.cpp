#include "JSONParser.hpp"

#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariant>

namespace application
{
bool JSONParser::loadJSONDocument(const std::string& absoluteConfigFilePath)
{
    bool foundFile = false;
    QString filePath = QString::fromStdString(absoluteConfigFilePath);
    if (QFileInfo::exists(filePath))
    {
        QFile file;

        file.setFileName(filePath);

        file.open(QIODevice::ReadOnly | QIODevice::Text);
        auto val = file.readAll();
        file.close();
        this->doc = QJsonDocument::fromJson(val);
        foundFile = true;
        this->docLoaded = true;
    }

    return foundFile;
}


std::vector<std::string> JSONParser::getOptionValues(const std::string& optionName) const
{
    std::vector<std::string> returnValue;

    if (this->docLoaded)
    {
        QString optionNameQ = QString::fromStdString(optionName);
        QJsonObject rootObj = doc.object().value("config").toObject();
        
        if (rootObj.value(optionNameQ).isArray())
        {
            foreach (const QJsonValue& value, rootObj[optionNameQ].toArray())
            {
                if (value.isString())
                {
                    returnValue.push_back(value.toString().toStdString());
                }
            }
        }
        else if (rootObj.value(optionNameQ).isString())
        {
            returnValue.push_back(rootObj.value(optionNameQ).toString().toStdString());
        }
        else if (rootObj.value(optionNameQ).isBool())
        {
            returnValue.push_back(QVariant(rootObj.value(optionNameQ).toBool()).toString().toStdString());
        }
    }

    return returnValue;
}
}  // namespace application