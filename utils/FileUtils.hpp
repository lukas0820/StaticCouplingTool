#ifndef STATICCOUPLINGANALYZER_FILEUTILS_H
#define STATICCOUPLINGANALYZER_FILEUTILS_H

#include <string>

namespace utils
{
class FileUtils
{
public:
    static std::string removeFileExtension(const std::string& fileName);

    static std::string getFileNameFromPath(const std::string& fileName);

    static std::string getFileNameWithoutExtensionFromPath(const std::string& fileName);
};

}  // namespace utils


#endif  // STATICCOUPLINGANALYZER_FILEUTILS_H
