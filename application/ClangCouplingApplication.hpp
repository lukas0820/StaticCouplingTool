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
    ClangCouplingApplication(coupling::IResultExporter* exporter);

private:
    bool isReadyForExecution() override;

private:
    language::cpp::ClangCouplingFinder clangCouplingFinder;
    coupling::FileCouplingAnalyser fileCouplingAnalyser;
};

}  // namespace application


#endif  // STATICCOUPLINGANALYZER_CLANGCOUPLINGAPPLICATION_HPP
