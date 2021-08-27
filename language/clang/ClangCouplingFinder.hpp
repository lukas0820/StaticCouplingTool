#ifndef STATICCPPCOUPLING_CLANGCOUPLINGFINDER_HPP
#define STATICCPPCOUPLING_CLANGCOUPLINGFINDER_HPP

#include <clang/Tooling/CompilationDatabase.h>

#include <map>
#include <string>
#include <vector>

#include "ICouplingFinder.hpp"

namespace language::cpp
{
class ClangCouplingFinder : public language::ICouplingFinder
{
public:
    /**
     * @brief Statuses of initialization.
     */
    enum class InitStatus
    {
        OK,             /*!< initialization was successful */
        FAILED,         /*!< initialization failed */
        NOT_INITIALIZED /*!< init not called yet */
    };

    struct ExecutionArguments
    {
        language::CouplingCallback couplingCallback;
        std::function<void(const std::string&)> finishedTranslationUnitCallback;
        std::function<void(const std::string&)> startedTranslationUnitCallback;
        std::vector<std::string> sourceFileList;

    };

    /**
     * @brief Constructor.
     */
    ClangCouplingFinder();

    /**
     * @brief Initialize
     * Parses the compilation database and returns its result and sets
     * @param compilationDatabaseDir path to directory which includes JSON file of compilation database
     * @return status of initialization
     */
    InitStatus init(const std::string& compilationDatabaseDir);

    /**
     * @brief Gets the current initialization status
     */
    InitStatus getInitStatus() const;

    /**
     * @brief Get all files from the compilation database.
     * Function can be used after successful initialization, otherwise the empty list is returned
     *
     * @return list of files from compilation database
     */
    std::vector<std::string> getCompilationDBFiles() const;

    /**
     * @copydoc
     */
    virtual void execute() override;

    virtual void registerCouplingCallback(size_t couplingId, CouplingCallback clb) override;

    virtual void unregisterCouplingCallback(size_t couplingId) override;

    /**
     * @brief Get the list of source file paths to be analyzed.
     * @return list of source files
     */
    std::vector<std::string> getSourceFiles() const;

    /**
     * @brief Set the list of source file paths to be analyzed.
     * @warning If a source file path is not in compilation database there can be errors while execution
     * @param sourceFiles list of source file paths
     */
    void setSourceFiles(const std::vector<std::string>& sourceFiles);


private:
    void receiveCallback(coupling::AbstractCoupling* coupling);

    void startedTranslationUnitCallback(const std::string& file);

    void finishedTranslationUnitCallback(const std::string& file);


private:
    std::map<size_t, language::CouplingCallback> callbackMap;

    /**
     * @brief Current initialization status.
     */
    InitStatus initStatus;

    /**
     * @brief Pointer to compilation database.
     */
    std::unique_ptr<clang::tooling::CompilationDatabase> database;

    /**
     * @brief Source file paths to be analyzed.
     */
    std::vector<std::string> sourceFiles;
};

}  // namespace language::cpp
#endif  // STATICCPPCOUPLING_CLANGCOUPLINGFINDER_HPP
