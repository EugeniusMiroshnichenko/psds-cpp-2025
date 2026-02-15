#include <cstring>
#include <algorithm>

class SimpleVector {
public:
    SimpleVector() = default;
    
    SimpleVector(size_t size, int value = 0) {
        Resize(size, value);
    }

    SimpleVector(std::initializer_list<int> init_list) 
        : size_(init_list.size()), capacity_(init_list.size()) {
        data_ = new int[capacity_];
        std::copy(init_list.begin(), init_list.end(), data_);
    }
    
    SimpleVector(const SimpleVector& other) 
        : size_(other.size_), capacity_(other.capacity_) {
        data_ = new int[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
    
    SimpleVector(SimpleVector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    SimpleVector& operator=(const SimpleVector& other) {
        if (this != &other) {
            delete[] data_;
            
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new int[capacity_];
            
            std::copy(other.data_, other.data_ + size_, data_);
        }
        return *this;
    }
    
    SimpleVector& operator=(SimpleVector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    ~SimpleVector() {
        delete[] data_;
    }
    
    void Swap(SimpleVector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
    
    int& operator[](size_t index) {
        return data_[index];
    }
    
    const int& operator[](size_t index) const {
        return data_[index];
    }
    
    size_t Size() const {
        return size_;
    }
    
    size_t Capacity() const {
        return capacity_;
    }
    
    bool Empty() const {
        return size_ == 0;
    }
    
    const int* Data() const {
        return data_;
    }
    
    int* begin() {
        return data_;
    }
    
    const int* begin() const {
        return data_;
    }
    
    int* end() {
        return data_ + size_;
    }
    
    const int* end() const {
        return data_ + size_;
    }
    
    void PushBack(int value) {
        if (size_ == capacity_) {
            // Условно удваиваем, может можно оптимальнее
            Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = value;
    }
    
    void PopBack() {
        if (size_ > 0) {
            --size_;
        }
    }
    
    int* Insert(const int* pos, int value) {
        if (pos < data_ || pos > data_ + size_) {
            return end();
        }
        
        size_t index = pos - data_;
        
        if (size_ == capacity_) {
            Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        
        for (size_t i = size_; i > index; --i) {
            data_[i] = data_[i - 1];
        }
        
        data_[index] = value;
        ++size_;
        
        return data_ + index;
    }
    
    int* Erase(const int* pos) {
        if (pos < data_ || pos >= data_ + size_) {
            return end();
        }
        
        size_t index = pos - data_;
        
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        
        --size_;
        
        return data_ + index;
    }
    
    void Clear() {
        size_ = 0;
    }
    
    void Resize(size_t new_size, int value = 0) {
        if (new_size > capacity_) {
            Reserve(new_size);
        }
        
        if (new_size > size_) {
            for (size_t i = size_; i < new_size; ++i) {
                data_[i] = value;
            }
        }
        
        size_ = new_size;
    }
    
    void Reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        
        int* new_data = new int[new_capacity];
        std::copy(data_, data_ + size_, new_data);
        
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
    
private:
    int* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

bool operator==(const SimpleVector& lhs, const SimpleVector& rhs) {
    if (lhs.Size() != rhs.Size()) return false;
    for (size_t i = 0; i < lhs.Size(); ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

bool operator!=(const SimpleVector& lhs, const SimpleVector& rhs) {
    return !(lhs == rhs);
}

void swap(SimpleVector& lhs, SimpleVector& rhs) noexcept {
    lhs.Swap(rhs);
}