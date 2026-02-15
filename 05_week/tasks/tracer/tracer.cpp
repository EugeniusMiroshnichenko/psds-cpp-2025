#include <string>


class Tracer {
    public:
        static size_t count;
        static size_t default_ctor;
        static size_t str_ctor;
        static size_t copy_ctor;
        static size_t move_ctor;
        static size_t copy_assign;
        static size_t move_assign;
        static size_t dtor;
        static size_t alive;

        Tracer() : id_(++count), data_ {new char[1]()} {
            name_ = "obj_" + std::to_string(id_);
            ++default_ctor;
            ++alive; 
        }
        Tracer(std::string str) : id_(++count) {
            name_ = str + "_" + std::to_string(id_);
            data_ = new char[name_.length() + 1]();  // выделяем нужный размер + 1 для '\0'
            strcpy(data_, name_.c_str());
            ++str_ctor;
            ++alive;
        }

        Tracer(const Tracer& other) : id_(++count) {
            name_ = other.name_;
            data_ = new char[strlen(other.data_) + 1]();
            strcpy(data_, other.data_);
            ++copy_ctor;
            ++alive;
        }

        Tracer(Tracer&& other) noexcept : id_(++count), data_ {other.data_}, name_(std::move(other.name_)) {
            other.name_ = "";
            other.data_ = nullptr;
            ++move_ctor;
            ++alive;
        }

        Tracer& operator =(const Tracer& other){
            if (this != &other) {
                name_ = other.name_;

                delete[] data_;
                data_ = new char[1]();
                ++copy_assign;
            }
            return *this;
        }

        Tracer& operator =(Tracer&& other){
            if (this != &other) {
                name_ = std::move(other.name_);

                delete[] data_;
                data_ = other.data_;
                other.name_ = "";
                other.data_ = nullptr;
                ++move_assign;
            }
            return *this;
        }

        ~Tracer() {
            --alive;
            ++dtor;
            delete[] data_;
        }

        size_t Id() {
            return id_;
        }

        const std::string& Name() {
            return name_;
        }

        const char* Data() {
            return data_;
        }

        static void ResetStats() {
            count = 0;
            default_ctor = 0;
            str_ctor = 0;
            copy_assign = 0;
            copy_ctor = 0;
            move_assign = 0;
            move_ctor = 0;
            dtor = 0;
            alive = 0;
        }

    private:
        size_t id_;
        char* data_;
        std::string name_;
};

size_t Tracer::count = 0;
size_t Tracer::default_ctor = 0;
size_t Tracer::str_ctor = 0;
size_t Tracer::copy_ctor = 0;
size_t Tracer::move_ctor = 0;
size_t Tracer::copy_assign = 0;
size_t Tracer::move_assign = 0;
size_t Tracer::dtor = 0;
size_t Tracer::alive = 0;