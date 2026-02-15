#include <cstring>
#include <string>


class StringView {
    public:

        static const size_t npos;

        StringView() = default;
        StringView (const std::string& str, size_t pos = 0, size_t size = 0){
            if (pos > str.size() - 1) {return;}
            data_ = str.data();
            pos_ = pos;
            size_ = size == 0 ? str.size() - pos : std::min(size, str.size() - pos);
        }

        StringView (const char* str, size_t size = 0) : data_(str) {
            if (str == nullptr) return;
            size_t len = (size == 0) ? strlen(str) : size;
            pos_ = 0;
            size_ = std::min(len, (size == 0) ? strlen(str) : size);
        }
        
        char operator[](size_t idx) const {
            return data_[pos_ + idx];
        }

        const char* Data() const{
            return data_+ pos_;
        }

        char Front(){
            return data_[pos_];
        }

        char Back(){
            return data_[size_ - 1];
        }

        size_t Size() const{
            return size_;
        }

        size_t Length() const{
            return size_;
        }

        bool Empty() const{
            return size_ == 0;
        }

        void RemovePrefix(size_t idx) {
            if (idx >= size_) {
                size_ = 0;
            } else {
                pos_ += idx;
                size_ -= idx;
            }
        }

        void RemoveSuffix(size_t idx){
            size_ = idx >= size_ ? 0 : size_ - idx;
        }

        StringView Substr(size_t start_pos = 0, size_t count = 0) const {
            if (start_pos >= size_) {
                return StringView();
            }
            
            size_t new_count = (count == 0 || count > size_ - start_pos) 
                                ? size_ - start_pos 
                                : count;
            
            StringView result;
            result.data_ = data_ + pos_ + start_pos;
            result.pos_ = 0;
            result.size_ = new_count;
            return result;
        }

        size_t Find(char ch, size_t start_pos = 0) const {
            if (size_ == 0 || start_pos >= size_) {
                return npos;
            }
            
            for (size_t i = start_pos; i < size_; ++i) {
                if (data_[pos_ + i] == ch) {
                    return i;
                }
            }
            return npos;
        }
        
        size_t Find(const StringView& sv, size_t start_pos = 0) const {
            if (sv.size_ == 0) {
                return (start_pos <= size_) ? start_pos : npos;
            }
            
            if (start_pos >= size_ || sv.size_ > size_ - start_pos) {
                return npos;
            }
            
            for (size_t i = start_pos; i <= size_ - sv.size_; ++i) {
                bool found = true;
                for (size_t j = 0; j < sv.size_; ++j) {
                    if (data_[pos_ + i + j] != sv.data_[sv.pos_ + j]) {
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
    
        std::string ToString() const {
            return std::string(data_ + pos_, size_);
        }
    
    private:
        const char* data_ = nullptr;
        size_t pos_ = 0;
        size_t size_ = 0;
};

const size_t StringView::npos = -1;