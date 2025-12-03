#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>

void PrintingFunc(unsigned char* byte_ptr, size_t bytes, bool shouldInverse){
    std::ostringstream oss;
    oss << "0x";
    
    for (size_t i = 0; i < bytes; ++i) {
        size_t index = shouldInverse ? (bytes - 1 - i) : i;
        oss << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
            << static_cast<int>(byte_ptr[index]);
    }
    
    oss << "\n";
    std::cout << oss.str();
}

void PrintMemory(int number, bool shouldInverse=false) {
    unsigned char* byte_ptr = reinterpret_cast<unsigned char*>(&number);
    PrintingFunc(byte_ptr, 4, shouldInverse);
}

void PrintMemory(double number, bool shouldInverse=false) {
    unsigned  char* byte_ptr = reinterpret_cast<unsigned  char*>(&number);
    PrintingFunc(byte_ptr, 8, shouldInverse);
}