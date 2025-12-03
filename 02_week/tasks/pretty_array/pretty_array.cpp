#include <stdexcept>


void PrintArray(const int* start, const int* end, size_t limit = 0) {
    std::string result = "[";
    size_t counter = 0;
    for (; start!=end; ++start){
        ++counter;
        result += std::to_string(*start);
        if (end - start - 1 == 0){
            // Последний элемент
            continue;
        }
        else if ((limit != 0) && counter == limit)
        {
            // Переход на новую строку
            counter = 0;
            result += ", ...\n ";
        }
        else {
            // Просто некоторый элемент
            result += ", ";
        }
    }
    result += "]\n";
    std::cout << result;
}
