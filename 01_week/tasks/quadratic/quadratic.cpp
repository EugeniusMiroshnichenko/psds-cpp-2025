#include <stdexcept>
#include <cmath>
#include <iomanip>

bool isLevelLine(int a, int b){
    if (a == 0 && b == 0) return true;
    else return false;

}

bool isLinear(int a, int b){
    if (a == 0 && b != 0) return true;
    else return false;

}

bool isQuadratic(int a){
    if (a != 0) return true;
    else return false;

}

std::string AddRootToStr(double x){
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6);
    if (std::abs(x - std::round(x)) < 1e-10) {
        oss << static_cast<int>(std::round(x));
    } else {
        oss << x;
    }
    return oss.str();
}

void SolveQuadratic(int a, int b, int c) {
    std::string result = "";
    if (isLevelLine(a, b)){
        if (c == 0) result = "infinite solutions";
        else result = "no solutions";
    }
    else if (isLinear(a, b)){
        double x = -static_cast<double>(c) / b;
        result = AddRootToStr(x);
    }
    else if (isQuadratic(a)){
        double discr = b * b - 4 * a * c;
        if (discr < 0) {
            result = "no solutions";
        }
        else if (std::abs(discr) < 1e-10) {
            double x = -b / (2.0 * a);
            result = AddRootToStr(x);
        }
        else {
            double x1 = (-b + sqrt(discr)) / (2.0 * a);
            double x2 = (-b - sqrt(discr)) / (2.0 * a);
            
            if (x1 > x2) std::swap(x1, x2);
            result = AddRootToStr(x1) + " " + AddRootToStr(x2);
        }
    }

    std::cout << result;
}