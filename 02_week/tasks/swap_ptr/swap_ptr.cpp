#include <stdexcept>

template<typename T>
// Сделаем через generic, главное чтобы приходил какой-то указатель
void SwapPtr(T*& ptr1, T*& ptr2) {
    T* temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
}
