#include "JSONExporter.hpp"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <iostream>
#include <map>

#include "FileUtils.hpp"

using utils::FileUtils;

namespace coupling
{
JSONExporter::JSONExporter(const std::string& outputPath) : outputPath(outputPath) {}
void JSONExporter::exportCoupling(const CouplingGraph& couplingGraph)
{
    QJsonDocument doc;

    QJsonArray nodes;
    auto nodeList = couplingGraph.getNodes();
    std::map<std::string, int> nodeToIndexMap;

    for (int i = 0; i < nodeList.size(); i++)
    {
        auto currentNode = nodeList[i];
        nodeToIndexMap[currentNode] = i;
        QJsonObject jsonNode;
        jsonNode.insert(
            "id", QJsonValue::fromVariant(QVariant(QString("%1:%2").arg(i).arg(QString::fromStdString(currentNode)))));
        jsonNode.insert("label", QJsonValue::fromVariant(QString::fromStdString(currentNode)));
        jsonNode.insert("value", QJsonValue::fromVariant(1));
        nodes.push_back(jsonNode);
    }

    QJsonArray edges;
    for (auto currentEdge : couplingGraph.getCoupling())
    {
        QJsonObject jsonEdge;
        QString callerId =
            QString("%1:%2").arg(nodeToIndexMap.at(currentEdge.caller)).arg(QString::fromStdString(currentEdge.caller));
        QString calleeId =
            QString("%1:%2").arg(nodeToIndexMap.at(currentEdge.callee)).arg(QString::fromStdString(currentEdge.callee));
        jsonEdge.insert("id", QJsonValue::fromVariant(QString("%1::%2").arg(calleeId).arg(calleeId)));
        jsonEdge.insert("directed", QJsonValue::fromVariant(true));
        jsonEdge.insert("start", QJsonValue::fromVariant(callerId));
        jsonEdge.insert("end", QJsonValue::fromVariant(calleeId));
        jsonEdge.insert("weight", QJsonValue::fromVariant(static_cast<int>(currentEdge.couplingCount)));
        edges.push_back(jsonEdge);
    }

    QJsonObject root;
    root.insert("nodes", nodes);
    root.insert("edges", edges);
    doc.setObject(root);


    if (FileUtils::isFolder(this->outputPath) && !this->outputPath.empty())
    {
        int i = 0;
        QString path = QString::fromStdString(this->outputPath).append("/%1").arg(i);
        while (FileUtils::isFolder(path.toStdString()))
        {
            i++;
            path = QString::fromStdString(this->outputPath).append("/%1").arg(i);
        }
        
        QDir().mkpath(path);

        this->outputPath = path.toStdString();

        path = path.append("/results.json");

        QFile file(path);
        if (file.open(QIODevice::ReadWrite))
        {
            file.write(doc.toJson());
        }

        file.close();
    }
}

std::string JSONExporter::getPath() const
{
    return this->outputPath;
}
}  // namespace coupling