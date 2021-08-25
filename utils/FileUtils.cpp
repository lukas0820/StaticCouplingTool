#include "FileUtils.hpp"

namespace utils
{
std::string FileUtils::removeFileExtension(const std::string& fileName)
{
    std::string fileNameWithoutExtension = "";
    if (fileName.find(".") != std::string::npos)
    {
        fileNameWithoutExtension = fileName.substr(0, fileName.find_last_of("."));
    }

    return fileNameWithoutExtension;
}
}  // namespace utils
