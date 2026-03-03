template<typename T>
class subvector {
    T *mas;
    unsigned int top;
    unsigned int capacity;
     
public:
    subvector();
    ~subvector();
    subvector(const subvector& other);
    subvector& operator=(const subvector& other);
    subvector(subvector&& other);
    subvector& operator=(subvector&& other);

    bool push_back(const T& d);
    T pop_back();
    bool resize(unsigned int new_capacity);
    void shrink_to_fit();
    void clear();
    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;
    unsigned int size() const;
    unsigned int get_capacity() const;
};
