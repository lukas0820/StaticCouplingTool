#ifndef STATICCOUPLINGANALYZER_CONTAINTERUTILS_H
#define STATICCOUPLINGANALYZER_CONTAINTERUTILS_H

#include <algorithm>
#include <vector>

namespace utils
{
class ContainerUtils
{
public:
    template <class T>
    static bool isInVector(std::vector<T> vector, T value)
    {
        return std::find(vector.begin(), vector.end(), value) != vector.end();
    }
};
}  // namespace utils


#endif  // STATICCOUPLINGANALYZER_CONTAINTERUTILS_H
