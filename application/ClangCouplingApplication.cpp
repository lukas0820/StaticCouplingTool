#include "ClangCouplingApplication.hpp"

#include "ConfigurationManager.hpp"
#include "ContainerUtils.hpp"
#include "FileUtils.hpp"

using configuration::ConfigurationManager;
using coupling::IResultExporter;
using language::cpp::ClangCouplingFinder;
using shared::ContainerUtils;
using shared::FileUtils;

namespace application
{
const std::vector<std::string> ClangCouplingApplication::CLANG_FILE_EXTENSIONS = {"*.h", "*.hpp", "*.c", "*.cpp"};

ClangCouplingApplication::ClangCouplingApplication()
    : AbstractCouplingApplication(&this->clangCouplingFinder, &this->fileCouplingAnalyser)
{
}

bool ClangCouplingApplication::isReadyForExecution()
{
    ConfigurationManager* manager = ConfigurationManager::getInstance();

    auto whiteList = getFileListFromPathList(manager->getOptionValues("whitelist"));
    auto blacklist = getFileListFromPathList(manager->getOptionValues("blacklist"));

    this->clangCouplingFinder.setBlackList(blacklist);
    this->clangCouplingFinder.setWhiteList(whiteList);

    ClangCouplingFinder::InitStatus status = this->clangCouplingFinder.init(this->projectFilePath);

    this->clangCouplingFinder.mergeHeaderAndSourceFiles(ConfigurationManager::getInstance()->hasOptionValue("merge"));
    return status == ClangCouplingFinder::InitStatus::OK;
}

std::vector<std::string> ClangCouplingApplication::getFileListFromPathList(const std::vector<std::string>& pathList)
{
    std::vector<std::string> returnList;
    for (auto pathListEntry : pathList)
    {
        if (shared::FileUtils::isFile(pathListEntry))
        {
            returnList.push_back(shared::FileUtils::getAbsoluteFilePath(pathListEntry));
        }
        else if (FileUtils::isFolder(pathListEntry))
        {
            for (auto s : FileUtils::getFileListRecursiveFromFolder(pathListEntry,
                                                                    ClangCouplingApplication::CLANG_FILE_EXTENSIONS))
            {
                returnList.push_back(s);
            }
        }
    }
    return returnList;
}
}  // namespace application