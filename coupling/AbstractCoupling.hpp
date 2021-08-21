//
// Created by lukas on 21.08.21.
//

#ifndef STATICCOUPLINGANALYZER_ABSTRACTCOUPLING_HPP
#define STATICCOUPLINGANALYZER_ABSTRACTCOUPLING_HPP

#include <string>

namespace coupling
{
#define COUPLING_CLASS                \
public:                               \
    static size_t getCouplingTypeId() \
    {                                 \
        static int id = 0;            \
        return (size_t)(&id);         \
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

private:
    std::string caller;
    std::string callee;
};
}  // namespace coupling
#endif  // STATICCOUPLINGANALYZER_ABSTRACTCOUPLING_HPP
