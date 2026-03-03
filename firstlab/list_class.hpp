struct Node {
    int value;
    Node* next;
};

class LinkedList {
    Node* head;
    int size;
public:
    LinkedList();
    void push_front(int val);
    void push_back(int val);
    void pop_front();
    void pop_back();
    int& front();
    int& back();
    int& operator[](int index);
    void insert(int index, int val);
    void delete_at(int index);
    void pretty_print();
};