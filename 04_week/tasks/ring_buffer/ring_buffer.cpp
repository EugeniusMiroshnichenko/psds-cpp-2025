#include <vector>
#include <algorithm>


class RingBuffer {
    public:
        RingBuffer(size_t size) {
            size_ = size > 0 ? size : 1;
            data_.resize(size_);
            counter_ = 0;
            pos_for_next_ = 0;
            oldest_ = 0;
        }
        RingBuffer(size_t size, int init_val) : RingBuffer(size) {
            for (std::vector<int>::iterator iter = data_.begin(); iter!=data_.end(); ++iter){
                *iter = init_val;
            }
            pos_for_next_ = 0;
            counter_ = size > 0 ? size : 1;
        }
        RingBuffer(std::initializer_list<int> initList) : RingBuffer(initList.size()) {
            data_.assign(initList.begin(), initList.end());
            pos_for_next_ = 0;
            counter_ = initList.size();
        }

        void Push(int val) {
            data_[pos_for_next_] = val;
            Increase_pos(pos_for_next_);
            if (counter_ == size_) {
                Increase_pos(oldest_);
                return;
            }
            ++counter_;
        }
        bool TryPush(int val) {
            if (counter_ == size_) {
                return false;
            }
            Push(val);
            return true;
        }
        void Pop() {
            if (counter_ == 0) {
                return;
            }
            Increase_pos(oldest_);
            --counter_;
        }
        bool TryPop(int& buffer) {
            if (counter_ == 0) {
                return false;
            }
            buffer = data_[oldest_];
            Pop();
            return true;
        }

        int& operator[](size_t index) {
            size_t actual_index = (oldest_ + index) % size_;
            return data_[actual_index];
        }

        const int& operator[](size_t index) const {
            size_t actual_index = (oldest_ + index) % size_;
            return data_[actual_index];
        }

        int& Front() {
            if (counter_ == 0){
                return *data_.begin();
            }
            size_t temp = pos_for_next_;
            Decrease_pos(temp);
            return data_[temp];
        }

        int& Back() {
            if (counter_ == 0){
                return *data_.begin();
            }
            return data_[oldest_];
        }

        bool Empty(){
            return (counter_ == 0);
        }

        bool Full(){
            return (counter_ == size_);
        }

        size_t Size(){
            return counter_;
        }

        size_t Capacity(){
            return size_;
        }

        void Clear(){
            counter_ = 0;
            oldest_ = 0;
            pos_for_next_ = 0;
        }

        std::vector<int> Vector() {
            std::vector<int> result;
            result.reserve(counter_);
            size_t temp_oldest = oldest_;
            for (size_t i = 0; i != counter_; ++i){
                result.push_back(data_[temp_oldest]);
                Increase_pos(temp_oldest);
            }
            return result;
        }

        void Resize(size_t new_size){
            std::vector<int> new_data;
            new_size = new_size > 0 ? new_size : 1; 
            new_data.resize(new_size);
            size_t new_counter = 0;
            size_t start_pos = 0;

            // Copying
            if (new_size > size_) {
                start_pos = oldest_;
            }
            else if (counter_ > new_size) {
                start_pos = pos_for_next_;
                for (size_t i = 0; i != new_size; ++i){
                    Decrease_pos(start_pos);
                }
            }
            else {
                start_pos = 0;
            }
            for (size_t i = start_pos; new_counter != std::min(new_size, counter_); Increase_pos(i)){
                new_data[new_counter] = data_[i];
                ++new_counter;
            }

            // Other data
            if (new_size > size_) {
                pos_for_next_ = new_counter;
            }
            else {
                pos_for_next_ = 0;
                oldest_ = 0;
            }
            size_ = new_size;
            data_ = new_data;
            counter_ = new_counter;
        }

    protected:
        std::vector<int> data_;
        size_t size_;
        size_t pos_for_next_;
        size_t oldest_;
        size_t counter_;

        void Increase_pos(size_t& pos) {
            if (pos == size_ - 1) {
                pos = 0;
                return;
            }
            ++pos;
        }
        void Decrease_pos(size_t& pos) {
            if (pos == 0) {
                pos = size_ - 1;
                return;
            }
            --pos;
        }
};
