#ifndef STATICCOUPLINGANALYZER_CLANGCOUPLINGAPPLICATION_HPP
#define STATICCOUPLINGANALYZER_CLANGCOUPLINGAPPLICATION_HPP

#include "AbstractCouplingApplication.hpp"
#include "ClangCouplingFinder.hpp"
#include "FileCouplingAnalyser.hpp"
#include "IResultExporter.hpp"
namespace application
{
class ClangCouplingApplication : public AbstractCouplingApplication
{
public:
    ClangCouplingApplication();


private:
    bool isReadyForExecution() override;

    std::vector<std::string> getFileListFromPathList(const std::vector<std::string>& pathList);

private:
    static const std::vector<std::string> CLANG_FILE_EXTENSIONS;
    language::cpp::ClangCouplingFinder clangCouplingFinder;
    coupling::FileCouplingAnalyser fileCouplingAnalyser;
};

}  // namespace application


#endif  // STATICCOUPLINGANALYZER_CLANGCOUPLINGAPPLICATION_HPP
