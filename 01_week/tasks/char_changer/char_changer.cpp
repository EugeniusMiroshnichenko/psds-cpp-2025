#include <cstddef>
#include <stdexcept>
#include <cctype>


size_t Counter(char array[], size_t size, size_t startIdx){
    char symbol = array[startIdx];
    size_t count = 1;
    for (size_t i=startIdx+1; i<size-1; ++i){
        if (array[i] == symbol) ++count;
        else break;
    }
    return count;
}

size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    char result[256];
    size_t count = 0;
    size_t new_ar_pos = 0;
    for (size_t i=0; i<size-1;){
        count = Counter(array, size, i);

        if (array[i] == ' '){
            result[new_ar_pos] = delimiter;
        }
        else if (array[i] >= +'0' && array[i] <= +'9'){
            result[new_ar_pos] = '*';
            if (count >= 10){
                ++new_ar_pos;
                result[new_ar_pos] = '0';
            }
            else if (count > 1){
                ++new_ar_pos;
                result[new_ar_pos] = count + '0';
            }
        }
        else if (array[i] >= +'a' && array[i] <= +'z'){
            result[new_ar_pos] = std::toupper(array[i]);
            if (count >= 10){
                ++new_ar_pos;
                result[new_ar_pos] = '0';
            }
            else if (count > 1){
                ++new_ar_pos;
                result[new_ar_pos] = count + '0';
            }
        }
        else if (array[i] >= +'A' && array[i] <= +'Z'){
            result[new_ar_pos] = array[i];
            if (count >= 10){
                ++new_ar_pos;
                result[new_ar_pos] = '0';
            }
            else if (count > 1){
                ++new_ar_pos;
                result[new_ar_pos] = count + '0';
            }
        }
        else{
            result[new_ar_pos] = '_';
            if (count >= 10){
                ++new_ar_pos;
                result[new_ar_pos] = '0';
            }
            else if (count > 1){
                ++new_ar_pos;
                result[new_ar_pos] = count + '0';
            }
        }
        i += count;
        ++new_ar_pos;
    }
    for (size_t i = 0; i < new_ar_pos && i < size - 1; ++i) {
        array[i] = result[i];
    }
    array[std::min(new_ar_pos, size - 1)] = '\0';
    return new_ar_pos;
}

