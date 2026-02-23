#include <string>


class UniquePtr {
    public:
        UniquePtr() = default;

        UniquePtr(std::string* ptr) : ptr_(ptr) {}

        UniquePtr(UniquePtr& other) = delete;

        UniquePtr(UniquePtr&& other) noexcept {
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        };

        UniquePtr& operator=(UniquePtr& other) = delete;

        UniquePtr& operator=(UniquePtr&& other) noexcept {
            if (this != &other){
                delete ptr_;
                ptr_ = other.ptr_;
                other.ptr_ = nullptr;
            }
            return *this;
        };

        ~UniquePtr() {
            delete ptr_;
        }

        std::string* Get() {
            return ptr_;
        }

        explicit operator bool() const {
            return ptr_ != nullptr;
        }

        std::string& operator*() {
            return *ptr_;
        }

        std::string* operator->() {
            return ptr_;
        }

        std::string* Release() {
            std::string* temp = ptr_;
            ptr_ = nullptr;
            return temp;
        }

        void Reset(std::string* ptr = nullptr) {
            delete ptr_;
            ptr_ = ptr;
        }

        void Swap(UniquePtr& other) {
            std::swap(ptr_, other.ptr_);
        }

    private:
        std::string* ptr_ = nullptr;
};

void Swap(UniquePtr& lhs ,UniquePtr& rhs) {
    lhs.Swap(rhs);
}

UniquePtr MakeUnique(std::string str) {
    return UniquePtr(new std::string(std::move(str)));
}