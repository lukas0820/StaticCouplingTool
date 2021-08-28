#include "ClangCouplingApplication.h"

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
    std::vector<std::string> fileList = this->clangCouplingFinder.getCompilationDBFiles();
    this->fileCouplingAnalyser.init(fileList);

    return status == ClangCouplingFinder::InitStatus::OK;
}
}  // namespace application