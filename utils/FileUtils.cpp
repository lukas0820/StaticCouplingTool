#include "FileUtils.hpp"

namespace utils
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
}  // namespace utils
