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

    /**
     * @brief Arguments that are needed for the analysis.
     */
    struct ExecutionArguments
    {
        language::CouplingCallback couplingCallback;
        std::function<void(const std::string&)> finishedTranslationUnitCallback;
        std::function<void(const std::string&)> startedTranslationUnitCallback;
        std::vector<std::string> sourceFileList;
        bool merge = false;
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
     * @copydoc ICouplingFinder::execute()
     */
    virtual void execute() override;

    /**
     * @copydoc ICouplingFinder::registerCouplingCallback()
     */
    virtual void registerCouplingCallback(CouplingCallback clb) override;

    /**
     * @copydoc ICouplingFinder::registerProgressCallback()
     * @warning The filename (third argument of callback function) is currently not supported. It always will receive the empty string
     */
    virtual void registerProgressCallback(ProgressCallback clb) override;

    /**
     * @brief If set, header and source files are handled as the same file internally.
     * This causes that coupling from header to source or vice versa is not longer found.
     */
    void mergeHeaderAndSourceFiles(bool merge);

    /**
     * @brief Only files that are in passed list will be analysed.
     * If also a blacklist is set, file contained in the blacklist are removed from this list.
     */
    void setWhiteList(const std::vector<std::string>& whiteList);

    /**
     * @brief Files that are on the passed list are ignored in the analyse.
     */
    void setBlackList(const std::vector<std::string>& blackList);


private:
    /**
     * @brief whitelist.
     */
    std::vector<std::string> whiteList;

    /**
     * @brief blacklist.
     */
    std::vector<std::string> blackList;

    /**
     *
     * @param coupling
     */
    void receiveCallback(shared::AbstractCoupling* coupling);


    void startedTranslationUnitCallback(const std::string& file);

    void finishedTranslationUnitCallback(const std::string& file);

    std::vector<std::string> getFilesToAnalyse();


private:
    language::CouplingCallback callback;

    language::ProgressCallback  progressCallback;

    bool merge = false;

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
