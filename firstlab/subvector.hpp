struct subvector {
    int* mas;
    unsigned int top;
    unsigned int capacity;
};

bool init(subvector* qv);
bool resize(subvector* qv, unsigned int new_capacity);
void clear(subvector* qv);
void destructor(subvector* qv);
void shrink_to_fit(subvector* qv);
bool push_back(subvector* qv, int d);
int pop_back(subvector* qv);