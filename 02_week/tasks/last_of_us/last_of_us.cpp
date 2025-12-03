#include <stdexcept>


const int* FindLastElement(const int* begin, const int* end, bool (*predicate)(int)) {
    const int* result = end;
    if ((begin == nullptr) || (end==nullptr) || (predicate == nullptr) || (begin > end)){
        result = end;
        return result;
    }

    for (; begin != end; ++begin){
        const int elem = *begin;
        if (predicate(elem)){
            result = begin;
        }
    }

    return result;
}