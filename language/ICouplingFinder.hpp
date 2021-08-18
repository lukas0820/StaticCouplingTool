#ifndef STATICCPPCOUPLING_ICOUPLINGFINDER_H
#define STATICCPPCOUPLING_ICOUPLINGFINDER_H
namespace language
{
class ICouplingFinder
{
public:
    /**
     * @brief Executes the coupling finder and blocks until it has finished.
     */
    virtual void execute() = 0;
};
}  // namespace language


#endif  // STATICCPPCOUPLING_ICOUPLINGFINDER_H
