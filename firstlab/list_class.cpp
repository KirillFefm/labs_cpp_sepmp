#include <iostream>
#include "list_class.hpp"

struct Node{
    int value;
    Node* next;
};

class LinkedList{
    Node* head;
    int size;
  public:
    LinkedList() {
      head = nullptr;
      size = 0;
    }

    void push_front(int val) {
        Node* new_node = new Node{val, head};
        head = new_node;
    }

    void push_back(int val) {
        Node* new_node = new Node{val, nullptr};
        if (!head) {
            head = new_node;
            return;
        }
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }

    void pop_front() {
        if (!head) return;
        Node* temp = head;
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
        Node* current = head;
        while (current->next && current->next->next) {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }

    int& front() {
        if (!head) throw std::out_of_range("");
        return head->value;
    }
    
    int& back() {
        if (!head) throw std::out_of_range("");
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        return current->value;
    }

    int& operator[](int index) {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            if (!current) throw std::out_of_range("");
            current = current->next;
        }
        if (!current) throw std::out_of_range("");
        return current->value;
    }

    void insert(int index, int val) {
        if (index == 0) {
            push_front(val);
            return;
        }
        Node* current = head;
        for (int i = 0; i < index - 1 && current; i++) {
            current = current->next;
        }
        if (!current) return;
        Node* new_Node = new Node{val, current->next};
        current->next = new_Node;
    }

    void delete_at(int index) {
        if (index == 0) {
            pop_front();
            return;
        }
        Node* current = head;
        for (int i = 0; i < index - 1 && current; i++) {
            current = current->next;
        }
        if (!current || !current->next) return;
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    void pretty_print() {
        Node* current = head;
        while (current) {
            std::cout << current->value << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};

int main() {
    LinkedList list;
    list.pretty_print();
    list.push_back(1);
    list.pretty_print();
    list.push_back(2);
    list.push_front(0);
    list.insert(1, 5);
    list.pretty_print();
    list.pop_back();
    list.delete_at(1);
    list.pretty_print();
    return 0;
}