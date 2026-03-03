template<typename T>
class subforwardlist {
    struct Node {
        T data;
        Node* next;
    };
    Node* begin;

public:
    subforwardlist();
    ~subforwardlist();
    subforwardlist(const subforwardlist& other);
    subforwardlist& operator=(const subforwardlist& other);
    subforwardlist(subforwardlist&& other);
    subforwardlist& operator=(subforwardlist&& other);

    void push_back(const T& data);
    T pop_back();
    void push_forward(const T& data);
    T pop_forward();
    void push_where(unsigned int where, const T& data);
    T erase_where(unsigned int where);
    unsigned int size();
};
