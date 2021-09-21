#ifndef STATICCOUPLINGANALYZER_FILEUTILS_H
#define STATICCOUPLINGANALYZER_FILEUTILS_H

#include <string>
#include <vector>

namespace shared
{
class FileUtils
{
public:
    static std::string removeFileExtension(const std::string& fileName);

    static std::string getFileNameFromPath(const std::string& fileName);

    static std::string getFileNameWithoutExtensionFromPath(const std::string& fileName);

    static bool isFile(const std::string& path);

    static bool isFolder(const std::string& path);

    static std::vector<std::string> getFileListRecursiveFromFolder(const std::string& folderPath,
                                                                   const std::vector<std::string>& nameFilters);
    static std::string getAbsoluteFilePath(const std::string& path);
};

}  // namespace shared


#endif  // STATICCOUPLINGANALYZER_FILEUTILS_H
