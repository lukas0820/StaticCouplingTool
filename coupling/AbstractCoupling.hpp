//
// Created by lukas on 21.08.21.
//

#ifndef STATICCOUPLINGANALYZER_ABSTRACTCOUPLING_HPP
#define STATICCOUPLINGANALYZER_ABSTRACTCOUPLING_HPP

#include <string>

namespace coupling
{
#define COUPLING_CLASS                       \
public:                                      \
    static size_t getCouplingClassTypeId()   \
    {                                        \
        static int id = 0;                   \
        return (size_t)(&id);                \
    }                                        \
                                             \
    virtual size_t getCouplingObjectTypeId() \
    {                                        \
        return getCouplingClassTypeId();     \
    }
class AbstractCoupling
{
    COUPLING_CLASS
public:
    const std::string& getCaller() const
    {
        return caller;
    }
    const std::string& getCallee() const
    {
        return callee;
    }

protected:
    std::string caller;
    std::string callee;
};

class FileCoupling : public AbstractCoupling
{
    COUPLING_CLASS
public:
    FileCoupling(const std::string& caller, const std::string& callee, const std::string& name = "default")
    {
        this->caller = caller;
        this->callee = callee;
        this->functionName = name;
    }

    const std::string& getFunctionName() const
    {
        return functionName;
    }

private:
    std::string functionName;
};
}  // namespace coupling
#endif  // STATICCOUPLINGANALYZER_ABSTRACTCOUPLING_HPP
