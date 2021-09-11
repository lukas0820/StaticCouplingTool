#include "FileUtils.hpp"

#include <QDirIterator>
#include <QFileInfo>

namespace shared
{
std::string FileUtils::removeFileExtension(const std::string& fileName)
{
    std::string fileNameWithoutExtension = fileName;
    if (fileName.find(".") != std::string::npos)
    {
        fileNameWithoutExtension = fileName.substr(0, fileName.find_last_of("."));
    }

    return fileNameWithoutExtension;
}

std::string FileUtils::getFileNameFromPath(const std::string& fileName)
{
    std::string fileNameFromPath = fileName;
    if (fileName.find("/") != std::string::npos)
    {
        fileNameFromPath = fileName.substr(fileName.find_last_of("/") + 1, fileName.size());
    }

    return fileNameFromPath;
}

std::string FileUtils::getFileNameWithoutExtensionFromPath(const std::string& fileName)
{
    std::string returnString = getFileNameFromPath(fileName);
    returnString = removeFileExtension(returnString);
    return returnString;
}

bool FileUtils::isFile(const std::string& path)
{
    QFileInfo info(QString::fromStdString(path));
    return info.exists() && info.isFile();
}

bool FileUtils::isFolder(const std::string& path)
{
    QFileInfo info(QString::fromStdString(path));
    return info.exists() && info.isDir();
}

std::vector<std::string> FileUtils::getFileListRecursiveFromFolder(const std::string& folderPath,
                                                                   const std::vector<std::string>& nameFilters)
{
    std::vector<std::string> returnList;

    QStringList filters;
    for (auto s : nameFilters)
    {
        filters.append(QString::fromStdString(s));
    }

    QDirIterator it(QString::fromStdString(folderPath), filters, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        returnList.push_back(it.next().toStdString());
    }

    return returnList;

}
}  // namespace shared
