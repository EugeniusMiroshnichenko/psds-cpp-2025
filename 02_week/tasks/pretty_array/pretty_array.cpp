#include <stdexcept>


void PrintArray(const int* start, const int* end, size_t limit = 0) {
    std::string result = "[";
    size_t counter = 0;

    if ((start!=nullptr) && (end!=nullptr)){
        bool startToEnd = end > start;
        const int* last_el_ptr = startToEnd ? end - 1 : end + 1;
        for (; start!=end; startToEnd ? ++start : --start){
            ++counter;
            result += std::to_string(*start);
            if (start == last_el_ptr){
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
    }

    result += "]\n";
    std::cout << result;
}
