//
// Created by lukas on 11.08.21.
//

#ifndef STATICCPPCOUPLING_CLANGCOUPLINGFINDER_HPP
#define STATICCPPCOUPLING_CLANGCOUPLINGFINDER_HPP

#include <string>
#include <vector>

#include "ICouplingFinder.hpp"


class ClangCouplingFinder : public language::ICouplingFinder
{
public:
    ClangCouplingFinder(const std::string& compilationDatabaseDir, const std::vector<std::string>& sourceFiles);

    virtual void execute() override;

private:
    const std::string compilationDatabaseDir;
    const std::vector<std::string> sourceFiles;
};


#endif  // STATICCPPCOUPLING_CLANGCOUPLINGFINDER_HPP
