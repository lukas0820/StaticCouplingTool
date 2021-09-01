#ifndef STATICCPPCOUPLING_ICOUPLINGFINDER_H
#define STATICCPPCOUPLING_ICOUPLINGFINDER_H

#include <functional>

#include "AbstractCoupling.hpp"

namespace language
{
typedef std::function<void(coupling::AbstractCoupling*)> CouplingCallback;
typedef std::function<void(size_t, size_t, const std::string&)> ProgressCallback;

class ICouplingFinder
{
public:
    /**
     * @brief Executes the coupling finder and blocks until it has finished.
     */
    virtual void execute() = 0;


    virtual void registerCouplingCallback(CouplingCallback clb) = 0;

    virtual void registerProgressCallback(ProgressCallback clb) = 0;
};
}  // namespace language


#endif  // STATICCPPCOUPLING_ICOUPLINGFINDER_H
