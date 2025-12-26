#include <vector>
#include <stack>
#include <algorithm>
#include <initializer_list>


class Queue {
    public:
        Queue() = default;
        Queue(int size){
            in_.reserve(size);
        }
        Queue(std::vector<int> vector){
            in_ = vector;
        }
        Queue(std::stack<int> stack){
            in_.reserve(stack.size());

            std::vector<int> temp;
            while (!stack.empty()) {
                temp.push_back(stack.top());
                stack.pop();
            }
            
            std::reverse(temp.begin(), temp.end());
            in_ = temp;

        }

        Queue(std::initializer_list<int> initList) {
            in_.reserve(initList.size());
            for (int val : initList) {
                in_.push_back(val);
            }
        }

        void Push(int in_num){
            in_.push_back(in_num);
        }

        bool Pop(){
            if (Empty()) return false;
            if (out_.empty()) In_to_out();
            out_.pop_back();
            return true;
        }

        bool Empty() const{
            return in_.empty() && out_.empty();
        }

        size_t Size() const{
            return in_.size() + out_.size();
        }

        void Clear(){
            in_.clear();
            out_.clear();
            in_.shrink_to_fit();
            out_.shrink_to_fit();
        }

        void Swap(Queue& other){
            std::swap(in_, other.in_);
            std::swap(out_, other.out_);

        }

        int& Front(){
            if (Empty()) {
                // UB
                return out_.back();
            }
            
            if (out_.empty()) {
                In_to_out();
            }
            
            return out_.back();
        }

        int& Back(){
            if (Empty()) {
                // UB
                return out_.front();
            }
            
            if (!in_.empty()) {
                // Если есть что-то в первом списке
                return in_.back();
            } 
            else {
                // Если есть нет, то с конца последнего
                return out_.front();
            }
        }

        const int& Front() const {
            if (Empty()) {
                return out_.back();
            }
            

            if (out_.empty()) {
                Queue temp = *this;
                temp.In_to_out();
                return temp.out_.back();
            }
            
            return out_.back();
        }

        const int& Back() const {
            if (Empty()) {
                return in_.back();
            }
            
            if (!in_.empty()) {
                return in_.back();
            } 
            else {
                return out_[0];
            }
        }

        bool operator==(const Queue& other) const{

            if (Size() != other.Size()){
                return false;
            }
            if (Empty()){
                if (other.Empty()){
                    return true;
                }
                return false;
            }
            Queue one = *this;
            Queue two = other;

            one.In_to_out();
            two.In_to_out();

            for (size_t i = 0; i!= Size(); ++i){
                if (one.out_[i] != two.out_[i]){
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const Queue& other) const{
            return ! (*this == other);
        }

    protected:
        std:: vector <int> in_{};
        std:: vector <int> out_{}; 

        void In_to_out(){
            if (in_.empty()) {
                return;
            }
            std::vector<int> new_out;
            new_out.reserve(out_.size() + in_.size());
            
            for (auto it = in_.rbegin(); it != in_.rend(); ++it) {
                new_out.push_back(*it);
            }
            
            for (auto it = out_.begin(); it != out_.end(); ++it) {
                new_out.push_back(*it);
            }

            out_.swap(new_out);
            in_.clear();
            in_.shrink_to_fit();
        }
};


