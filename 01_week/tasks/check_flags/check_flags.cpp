#include <cstdint>
#include <stdexcept>


enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};

void PrintCheckFlags(CheckFlags flags) {

    uint8_t flags_int = static_cast<uint8_t>(flags);
    if (flags_int > static_cast<uint8_t>(CheckFlags::ALL)) {
        std::cout << "";
        return;
    }

    std::string names[6] = {"TIME", "DATE", "USER", "CERT", "KEYS" , "DEST"};
    std::string result = "[";
    bool symbol_added = false;

    uint8_t mask = 1;
    for (size_t i = 0; i < 6; ++i) {
        mask = (1 << i);
        if (flags_int & mask) {
            if (symbol_added) {
                result += ",";
            }
            result += names[i];
            symbol_added = true;
        }
    }

    std::cout << result + "]";
}
