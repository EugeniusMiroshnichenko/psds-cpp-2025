#include <string>

struct ControlBlock {
    size_t shared_count;
    size_t weak_count;
    std::string* ptr;
    
    ControlBlock(std::string* p) : shared_count(1), weak_count(0), ptr(p) {}
};

class WeakPtr;

class SharedPtr {
public:
    SharedPtr() = default;
    
    SharedPtr(std::string* ptr) {
        if (ptr) {
            block_ = new ControlBlock(ptr);
        } else {
            block_ = nullptr;
        }
    }

    SharedPtr(const SharedPtr& other) : block_(other.block_) {
        if (block_) {
            ++(block_->shared_count);
        }
    }

    SharedPtr(SharedPtr&& other) noexcept : block_(other.block_) {
        other.block_ = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            block_ = other.block_;
            if (block_) {
                ++(block_->shared_count);
            }
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            block_ = other.block_;
            other.block_ = nullptr;
        }
        return *this;
    }

    ~SharedPtr() {
        release();
    }

    std::string* Get() {
        return block_ ? block_->ptr : nullptr;
    }

    void Reset(std::string* new_ptr = nullptr) {
        release();
        if (new_ptr) {
            block_ = new ControlBlock(new_ptr);
        } else {
            block_ = nullptr;
        }
    }

    void Swap(SharedPtr& other) {
        std::swap(block_, other.block_);
    }

    size_t UseCount() {
        return block_ ? block_->shared_count : 0;
    }

    explicit operator bool() const {
        return block_ && block_->ptr;
    }

    std::string& operator*() {
        return *(block_->ptr);
    }

    std::string* operator->() {
        return block_->ptr;
    }

private:
    ControlBlock* block_ = nullptr;

    void release() {
        if (block_) {
            --(block_->shared_count);
            if (block_->shared_count == 0) {
                delete block_->ptr;
                if (block_->weak_count == 0) {
                    delete block_;
                }
            }
        }
    }

    friend class WeakPtr;
};

class WeakPtr {
public:
    WeakPtr() = default;

    WeakPtr(const WeakPtr& other) : block_(other.block_) {
        if (block_) {
            ++(block_->weak_count);
        }
    }

    WeakPtr(WeakPtr&& other) noexcept : block_(other.block_) {
        other.block_ = nullptr;
    }

    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            release();
            block_ = other.block_;
            if (block_) {
                ++(block_->weak_count);
            }
        }
        return *this;
    }

    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if (this != &other) {
            release();
            block_ = other.block_;
            other.block_ = nullptr;
        }
        return *this;
    }

    WeakPtr(SharedPtr& shared) : block_(shared.block_) {
        if (block_) {
            ++(block_->weak_count);
        }
    }

    ~WeakPtr() {
        release();
    }

    bool Expired() {
        return !block_ || block_->shared_count == 0;
    }

    size_t UseCount() {
        return block_ ? block_->shared_count : 0;
    }

    explicit operator bool() const {
        return block_ && block_->ptr;
    }

    std::string& operator*() {
        return *(block_->ptr);
    }

    std::string* operator->() {
        return block_->ptr;
    }

    SharedPtr Lock() {
        if (Expired()) {
            return SharedPtr();
        }
        SharedPtr result;
        result.block_ = block_;
        ++(block_->shared_count);
        return result;
    }

    void Reset() {
        release();
        block_ = nullptr;
    }

    void Swap(WeakPtr& other) {
        std::swap(block_, other.block_);
    }

private:
    ControlBlock* block_ = nullptr;

    void release() {
        if (block_) {
            --(block_->weak_count);
            if (block_->shared_count == 0 && block_->weak_count == 0) {
                delete block_;
            }
        }
    }

    friend class SharedPtr;
};

void Swap(SharedPtr& lhs, SharedPtr& rhs) {
    lhs.Swap(rhs);
}

void Swap(WeakPtr& lhs, WeakPtr& rhs) {
    lhs.Swap(rhs);
}

SharedPtr MakeShared(std::string str) {
    return SharedPtr(new std::string(std::move(str)));
}