#include <vector>


class Stack {
    public:
        void Push(int num) {
            data_.push_back(num);
        }
        bool Pop() {
            if (data_.empty()) return false;
            data_.pop_back();
            return true;
        }
        const int& Top() const {
            if (data_.empty()){
                return *data_.begin();
            }
            return data_[data_.size()-1];
        }
        int& Top() {
            if (data_.empty()){
                return *data_.begin();
            }
            return data_[data_.size()-1];
        }
        bool Empty() const{
            return data_.empty();
        }
        size_t Size() const{
            return data_.size();
        }
        void Clear(){
            data_.clear();
        }
        void Swap(Stack& other){
            std::swap(this->data_, other.data_);
        }

        bool operator==(const Stack& other) const{
            if (Empty() && other.Empty()){
                return true;
            }
            if (Size() != other.Size()){
                return false;
            }
            for (size_t i=0; i!=Size(); ++i){
                if (data_[i] != other.data_[i]) return false;
            }
            return true;
        }
        bool operator!=(const Stack& other) const{
            return ! (*this==other);
        }
    
    private:
        std::vector<int> data_{};
};
