#ifndef STATICCPPCOUPLING_ICOUPLINGFINDER_H
#define STATICCPPCOUPLING_ICOUPLINGFINDER_H

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


    virtual void registerCouplingCallback(size_t couplingId, CouplingCallback clb) = 0;

    virtual void unregisterCouplingCallback(size_t couplingId) = 0;
};
}  // namespace language


#endif  // STATICCPPCOUPLING_ICOUPLINGFINDER_H
