#include <iostream>

template <typename T>
class Vector {
    T* data;
    unsigned int capacity;
    unsigned int length;
public:

    Vector(){
        capacity = 0;
        length = 0;
        data = nullptr;
        return;
    }

    ~Vector(){
        delete[] data;
    }
    bool resize(unsigned int new_capacity){
        if (new_capacity <= capacity) return false;
        T* new_data = new T[new_capacity];
        for (unsigned int i = 0; i < length; i++){
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
        return true;
    }
    void clear(){
        delete[] data;
        data = nullptr;
        capacity = 0;
        length = 0;
    }
    void shrink_to_fit(){
        resize(length);
    }
    void push_back(const T& value){
        if (length >= capacity){
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[length] = value;
        length++;
    }
    void pop_back(){
        if (length == 0) return;
        length--;
    }
    T& operator[](unsigned int index){
        if (index >= length) throw std::out_of_range("Index out of range");
        return data[index];
    }
    unsigned int size() const {
        return length;
    }
};
