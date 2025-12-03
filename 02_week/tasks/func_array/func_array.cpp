#include <stdexcept>


double ApplyOperations(double a, double b, double (*functions[])(double, double), size_t func_count) {
    double result = 0.0;
    const double& a_ref = a;
    const double& b_ref = b;
    for (size_t i=0; i<func_count; ++i){
        if (functions[i]){
            result += functions[i](a_ref, b_ref);
        }
    }
    return result;
}