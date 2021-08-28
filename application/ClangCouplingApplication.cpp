#include "ClangCouplingApplication.hpp"

#include "ConfigurationManager.hpp"

using coupling::IResultExporter;
using language::cpp::ClangCouplingFinder;

namespace application
{
ClangCouplingApplication::ClangCouplingApplication(IResultExporter* exporter)
    : AbstractCouplingApplication(&this->clangCouplingFinder, &this->fileCouplingAnalyser, exporter)
{
}

bool ClangCouplingApplication::isReadyForExecution()
{
    ClangCouplingFinder::InitStatus status = this->clangCouplingFinder.init(this->projectFilePath);
    this->clangCouplingFinder.mergeHeaderAndSourceFiles(ConfigurationManager::getInstance()->hasOptionValue("merge"));
    return status == ClangCouplingFinder::InitStatus::OK;
}
}  // namespace application