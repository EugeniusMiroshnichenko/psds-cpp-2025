#include <cstring>
#include <string>
#include <algorithm>

class CowString {
public:

    static const size_t npos;
    CowString() : data_(new InternalData()) {}
    
    CowString(const char* data) : data_(new InternalData(data)) {}
    
    CowString(const std::string& str) : data_(new InternalData(str)) {}
    
    CowString(const CowString& other) : data_(other.data_) {
        ++data_->ref_count_;
    }
    
    CowString(CowString&& other) noexcept 
        : data_(other.data_) {
        other.data_ = nullptr;
    }
    
    CowString& operator=(const CowString& other) {
        if (this != &other) {
            if (data_) {
                data_->decreaseRef();
            }
            data_ = other.data_;
            ++data_->ref_count_;
        }
        return *this;
    }
    
    CowString& operator=(CowString&& other) noexcept {
        if (this != &other) {
            if (data_) {
                data_->decreaseRef();
            }
            data_ = other.data_;
            other.data_ = nullptr;
        }
        return *this;
    }
    
    ~CowString() {
        if (data_) {
            data_->decreaseRef();
        }
    }
    
    size_t Size() const {
        return data_ ? data_->size_ : 0;
    }
    
    const char* ToCstr() const {
        return data_ ? data_->data_ : "";
    }
    
    std::string ToString() const {
        return data_ ? std::string(data_->data_, data_->size_) : std::string();
    }
    
    const char& operator[](size_t idx) const {
        return data_->data_[idx];
    }
    
    char& operator[](size_t idx) {
        make_copy_for_change();
        return data_->data_[idx];
    }
    
    operator const char*() const {
        return ToCstr();
    }
    
    CowString& Append(const char* str) {
        if (!str || *str == '\0') return *this;
        
        make_copy_for_change();
        
        size_t new_size = data_->size_ + strlen(str);
        if (new_size + 1 > data_->capacity_) {
            // Условно увелчичиваем в 2 раза
            size_t new_capacity = std::max(new_size + 1, data_->capacity_ * 2);
            char* new_data = new char[new_capacity];
            
            std::strcpy(new_data, data_->data_);
            std::strcat(new_data, str);
            
            delete[] data_->data_;
            data_->data_ = new_data;
            data_->size_ = new_size;
            data_->capacity_ = new_capacity;
        } else {
            std::strcat(data_->data_, str);
            data_->size_ = new_size;
        }
        return *this;
    }
    
    CowString& Append(const std::string& str) {
        Append(str.c_str());
        return *this;
    }
    
    CowString Substr(size_t pos = 0, size_t count = -1) const {
        if (!data_ || pos >= data_->size_) {
            return CowString();
        }
        
        size_t actual_count = count;
        // Если count == -1 (максимальное значение) или выходит за границы
        if (actual_count == static_cast<size_t>(-1) || pos + actual_count > data_->size_) {
            actual_count = data_->size_ - pos;
        }
        
        char* buffer = new char[actual_count + 1];
        std::copy(data_->data_ + pos, data_->data_ + pos + actual_count, buffer);
        buffer[actual_count] = '\0';
        
        CowString result(buffer);
        delete[] buffer;
        
        return result;
    }

    size_t Find(const std::string& str) const {
        if (str.empty()) {return 0;}
        
        if (!data_ || data_->size_ < str.length()) {
            return npos;
        }
        
        const char* str_converted_to_ch = str.c_str();
        
        for (size_t i = 0; i <= data_->size_ - str.length(); ++i) {
            bool found = true;
            for (size_t j = 0; j < str.length(); ++j) {
                if (data_->data_[i + j] != str_converted_to_ch[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return i;
            }
        }
        return npos;
    }

    size_t Find(const char ch) const {
        return Find(std::string(1, ch));
    }

    bool Empty() {
        return data_->size_ == 0;
    }

    
    void Clear() {
        make_copy_for_change();
        
        delete[] data_->data_;
        data_->data_ = new char[1];
        data_->data_[0] = '\0';
        data_->size_ = 0;
        data_->capacity_ = 1;
    }
    
private:
    struct InternalData {
        char* data_;
        size_t size_;
        size_t capacity_;
        size_t ref_count_;
        
        InternalData() :
            data_(new char[1]),
            size_(0),
            capacity_(1),
            ref_count_(1) {
            data_[0] = '\0';
        }
        
        InternalData(const char* data) :
            size_(data ? strlen(data) : 0),
            capacity_(size_ + 1),
            ref_count_(1) {
            data_ = new char[capacity_];
            if (data) {
                std::strcpy(data_, data);
            } else {
                data_[0] = '\0';
            }
        }
        
        InternalData(const std::string& str) :
            size_(str.length()),
            capacity_(size_ + 1),
            ref_count_(1) {
            data_ = new char[capacity_];
            std::strcpy(data_, str.c_str());
        }
        
        // Надо запретить констуркторы копирования и операторы присваивания копирования
        InternalData(const InternalData&) = delete;
        InternalData& operator=(const InternalData&) = delete;
        
        ~InternalData() {
            delete[] data_;
        }
        
        void decreaseRef() {
            if (--ref_count_ == 0) {
                delete this;
            }
        }
    };
    
    InternalData* data_;
    
    void make_copy_for_change() {
        if (data_ && data_->ref_count_ > 1) {
            InternalData* new_data = new InternalData(data_->data_);
            data_->decreaseRef();
            data_ = new_data;
        }
    }
};

const size_t CowString::npos = -1;