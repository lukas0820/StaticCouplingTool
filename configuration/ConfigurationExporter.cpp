#include "ConfigurationExporter.hpp"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariant>

namespace configuration
{
void ConfigurationExporter::addToExportConfiguration(const std::string& argumentName,
                                                     const std::vector<std::string>& entrys)
{
    size_t count = entrys.size();
    if (count > 0)
    {
        if (count == 1)
        {
            this->rootObject.insert(QString::fromStdString(argumentName),
                                    QJsonValue::fromVariant(QVariant(QString::fromStdString(entrys[0]))));
        }
        else
        {
            QJsonArray array;
            for (auto currentEntry : entrys)
            {
                array.push_back(QJsonValue::fromVariant(QVariant(QString::fromStdString(currentEntry))));
            }
            this->rootObject.insert(QString::fromStdString(argumentName), array);
        }
    }
}

void ConfigurationExporter::addToExportConfiguration(const std::string& argumentName, bool entry)
{
    this->rootObject.insert(QString::fromStdString(argumentName), QJsonValue::fromVariant(entry));
}

void ConfigurationExporter::exportConfiguration(const std::string& outputPath)
{
    QJsonDocument doc;
    doc.setObject(this->rootObject);

    QString path = QString::fromStdString(outputPath);
    QDir().mkpath(path);
    path = path.append("/configuration.json");

    QFile file(path);
    if (file.open(QIODevice::ReadWrite))
    {
        file.write(doc.toJson());
    }

    file.close();
}
}  // namespace application