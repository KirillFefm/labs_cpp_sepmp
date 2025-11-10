#include <iostream>


template <typename T>
struct Node{
    T value;
    Node* next;
};

template <typename T>
class List{
    Node<T>* head;
    int size;
  public:
    List() {
      head = nullptr;
      size = 0;
    }

    void push_front(T val) {
        Node<T>* new_node = new Node<T>{val, head};
        head = new_node;
    }

    void push_back(T val) {
        Node<T>* new_node = new Node<T>{val, nullptr};
        if (!head) {
            head = new_node;
            return;
        }
        Node<T>* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }

    void pop_front() {
        if (!head) return;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    void pop_back() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }
        Node<T>* current = head;
        while (current->next && current->next->next) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }

    T& front() {
        if (!head) throw std::out_of_range("");
        return head->value;
    }
    
    T& back() {
        if (!head) throw std::out_of_range("");
        Node<T>* current = head;
        while (current->next) {
            current = current->next;
        }
        return current->value;
    }

    T& operator[](int index) {
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            if (!current) throw std::out_of_range("");
            current = current->next;
        }
        if (!current) throw std::out_of_range("");
        return current->value;
    }

    void insert(int index, T val) {
        if (index == 0) {
            push_front(val);
            return;
        }
        Node<T>* current = head;
        for (int i = 0; i < index - 1 && current; i++) {
            current = current->next;
        }
        if (!current) return;
        Node<T>* new_Node = new Node<T>{val, current->next};
        current->next = new_Node;
    }

    void delete_at(int index) {
        if (index == 0) {
            pop_front();
            return;
        }
        Node<T>* current = head;
        for (int i = 0; i < index - 1 && current; i++) {
            current = current->next;
        }
        if (!current || !current->next) return;
        Node<T>* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    void pretty_print() {
        Node<T>* current = head;
        while (current) {
            std::cout << current->value << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};

int main() {
    std::cout << "--- Тест Int ---" << std::endl;
    List<int> list_int; 
    list_int.push_back(10);
    list_int.push_back(20);
    list_int.pretty_print(); 
    std::cout << "--- Тест Char ---" << std::endl;
    List<char> list_char;
    list_char.push_back('A'); 
    list_char.push_back('z');
    list_char.push_back(36); // $
    list_char.pretty_print(); 

    std::cout << "--- Тест Double ---" << std::endl;
    List<double> list_double;
    list_double.push_front(3.14);
    list_double.push_back(2.718);
    list_double.pretty_print(); 

    return 0;
}