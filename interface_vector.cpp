#include <iostream>

template<typename T>
class subvector {
     T *mas;
     unsigned int top;
     unsigned int capacity;
     
public:
     subvector(){
          capacity = 0;
          top = 0;
          mas = nullptr;
     }

     ~subvector(){
          delete[] mas;
     }

     subvector(const subvector& other){
          capacity = other.capacity;
          top = other.top;
          mas = new T[capacity];
          for(unsigned int i = 0; i < top; i++){
               mas[i] = other.mas[i];
          }
     }

     subvector& operator=(const subvector& other){
          if(this == &other) return *this;
          delete[] mas;
          capacity = other.capacity;
          top = other.top;
          mas = new T[capacity];
          for(unsigned int i = 0; i < top; i++){
               mas[i] = other.mas[i];
          }
          return *this;
     }

     subvector(subvector&& other) noexcept {
          mas = other.mas;
          capacity = other.capacity;
          top = other.top;
          other.mas = nullptr;
          other.capacity = 0;
          other.top = 0;
     }

     subvector& operator=(subvector&& other) noexcept {
          if(this == &other) return *this;
          delete[] mas;
          mas = other.mas;
          capacity = other.capacity;
          top = other.top;
          other.mas = nullptr;
          other.capacity = 0;
          other.top = 0;
          return *this;
     }

     bool push_back(const T& d){
          if(top >= capacity){
               if(!resize(capacity == 0 ? 1 : capacity * 2)) return false;
          }
          mas[top] = d;
          top++;
          return true;
     }

     T pop_back(){
          if(top == 0) return T{};
          top--;
          return mas[top];
     }

     bool resize(unsigned int new_capacity){
          if(new_capacity <= capacity) {
               if(top > new_capacity){
                    top = new_capacity;
               }
               return false;
          }
          T* new_mas = new T[new_capacity];
          for(unsigned int i = 0; i < top; i++){
               new_mas[i] = mas[i];
          }
          delete[] mas;
          mas = new_mas;
          capacity = new_capacity;
          return true;
     }

     void shrink_to_fit(){
          if(top == capacity) return;
          T* new_mas = new T[top];
          for(unsigned int i = 0; i < top; i++){
               new_mas[i] = mas[i];
          }
          delete[] mas;
          mas = new_mas;
          capacity = top;
     }

     void clear(){
          delete[] mas;
          mas = nullptr;
          capacity = 0;
          top = 0;
     }

     T& operator[](unsigned int index){
          return mas[index];
     }

     const T& operator[](unsigned int index) const {
          return mas[index];
     }

     unsigned int size() const {
          return top;
     }

     unsigned int get_capacity() const {
          return capacity;
     }
};




