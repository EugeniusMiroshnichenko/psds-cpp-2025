#include <string>

class SimpleList {
    public:
        SimpleList() {
            MakeFakeNode();
        }

        SimpleList(const SimpleList& other) : SimpleList() {
            Node* current = other.fake_->next_;
            while (current != other.fake_) {
                PushBack(std::string(*(current->data_)));
                current = current->next_;
            }
        }

        SimpleList(SimpleList&& other) noexcept 
            : fake_(other.fake_), size_(other.size_) {
            other.MakeFakeNode();
        }

        SimpleList& operator=(const SimpleList& other) {
            if (this != &other) {
                Clear();
                Node* current = other.fake_->next_;
                while (current != other.fake_) {
                    PushBack(std::string(*(current->data_)));
                    current = current->next_;
                }
            }
            return *this;
        }

        SimpleList& operator=(SimpleList&& other) noexcept {
            if (this != &other) {
                Clear();
                delete fake_;
                
                fake_ = other.fake_;
                size_ = other.size_;
                
                other.MakeFakeNode();
            }
            return *this;
        }

        ~SimpleList() {
            Clear();
            delete fake_;
        }

        size_t Size() const {
            return size_;
        }

        std::string& Front() const {
            return *(fake_->next_->data_);
        }

        std::string& Back() const {
            return *(fake_->prev_->data_);
        }

        void PushBack(std::string& str) {
            Node* el = new Node(&str, fake_->prev_, fake_);
            fake_->prev_->next_ = el;
            fake_->prev_ = el;
            ++size_;
        }

        void PushBack(std::string&& str) {
            Node* el = new Node(new std::string(std::move(str)), fake_->prev_, fake_);
            fake_->prev_->next_ = el;
            fake_->prev_ = el;
            ++size_;
        }

        void PushFront(std::string& str) {
            Node* el = new Node(new std::string(str), fake_, fake_->next_);
            fake_->next_->prev_ = el;
            fake_->next_ = el;
            ++size_;
        }

        void PushFront(std::string&& str) {
            Node* el = new Node(new std::string(std::move(str)), fake_, fake_->next_);
            fake_->next_->prev_ = el;
            fake_->next_ = el;
            ++size_;
        }

        void PopFront() {
            if (Empty()) {
                return;
            }
            Node* cur = fake_->next_;

            cur->next_->prev_ = cur->prev_;
            cur->prev_->next_ = cur->next_;
            
            delete cur;

            --size_;
        }

        void PopBack() {
            if (Empty()) {
                return;
            }
            Node* cur = fake_->prev_;

            cur->next_->prev_ = cur->prev_;
            cur->prev_->next_ = cur->next_;
            
            delete cur;

            --size_;
        }

        bool Empty() const {
            return (size_ == 0);
        }

        void Clear() {
            while(!Empty()){
                Node* current = fake_->next_;
                
                current->prev_->next_ = current->next_;
                current->next_->prev_ = current->prev_;
                
                delete current;
                --size_;
            }
        }

        void Swap(SimpleList& other) {
            std::swap(fake_, other.fake_);
            size_t temp = size_;
            size_ = other.size_;
            other.size_ = temp;
        }

    private:
        struct Node {
            Node() = default;
            Node(std::string* data, Node* prev, Node* next) :
                data_(data),
                prev_(prev),
                next_(next) {}

            ~Node() {
                delete data_;
            }
            std::string* data_ = nullptr;
            Node* prev_ = nullptr;
            Node* next_ = nullptr;
        };

        Node* fake_ = nullptr;
        size_t size_ = 0;

        void MakeFakeNode(){
            fake_ = new Node();
            fake_->prev_ = fake_;
            fake_->next_ = fake_;
            size_ = 0;
        }
};

void Swap(SimpleList& lhs, SimpleList& rhs) {
    lhs.Swap(rhs);
}