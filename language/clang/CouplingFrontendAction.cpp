#include "CouplingFrontendAction.hpp"

using clang::tooling::FrontendActionFactory;


namespace language::cpp
{
CouplingFrontendAction::CouplingFrontendAction(ClangCouplingFinder::ExecutionArguments args) : executionArguments(args)
{
}


std::unique_ptr<clang::ASTConsumer> CouplingFrontendAction::CreateASTConsumer(clang::CompilerInstance& compiler,
                                                                              llvm::StringRef file)
{
    return std::make_unique<CouplingASTConsumer>(&compiler.getASTContext());
}


std::unique_ptr<clang::tooling::FrontendActionFactory>
language::cpp::CouplingFrontendAction::createFrontendActionFactory(ClangCouplingFinder::ExecutionArguments args)
{
    class CouplingFrontendActionFactory : public FrontendActionFactory
    {
    public:
        CouplingFrontendActionFactory(ClangCouplingFinder::ExecutionArguments args) : args(args){};

        std::unique_ptr<FrontendAction> create() override
        {
            return std::make_unique<CouplingFrontendAction>(this->args);
        }

    private:
        ClangCouplingFinder::ExecutionArguments args;
    };
    return std::unique_ptr<FrontendActionFactory>(new CouplingFrontendActionFactory(args));
}

}  // namespace language::cpp