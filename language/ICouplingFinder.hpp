#ifndef STATICCPPCOUPLING_ICOUPLINGFINDER_H
#define STATICCPPCOUPLING_ICOUPLINGFINDER_H

#include <functional>

#include "AbstractCoupling.hpp"

namespace language
{
typedef std::function<void(coupling::AbstractCoupling*)> CouplingCallback;

class ICouplingFinder
{
public:
    /**
     * @brief Executes the coupling finder and blocks until it has finished.
     */
    virtual void execute() = 0;


    virtual void registerCouplingCallback(CouplingCallback clb) = 0;
};
}  // namespace language


#endif  // STATICCPPCOUPLING_ICOUPLINGFINDER_H
