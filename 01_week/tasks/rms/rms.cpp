#include <cstddef>
#include <cmath>


double CalculateRMS(double values[], size_t size) {
    double res = 0.0;
    if (values == nullptr || size == 0) return res;
    for (size_t i=0; i < size; ++i){
        res += values[i] * values[i];
    }
    return std::sqrt(res / size);
}