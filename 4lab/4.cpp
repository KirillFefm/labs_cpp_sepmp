#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <iterator>
#include <type_traits>
#include <utility>

template <typename RandomAccessIterator, typename Compare>
void sift_down(RandomAccessIterator first,
               std::size_t start,
               std::size_t heap_size,
               Compare comp) {
    std::size_t root = start;

    while (true) {
        std::size_t left = 2 * root + 1;
        if (left >= heap_size) {
            break;
        }

        std::size_t best = root;
        std::size_t right = left + 1;

        if (comp(*(first + best), *(first + left))) {
            best = left;
        }
        if (right < heap_size && comp(*(first + best), *(first + right))) {
            best = right;
        }

        if (best == root) {
            break;
        }

        std::iter_swap(first + root, first + best);
        root = best;
    }
}

template <typename RandomAccessIterator, typename Compare>
void simple_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    std::size_t n = static_cast<std::size_t>(last - first);
    if (n < 2) {
        return;
    }

    for (std::size_t i = n / 2; i > 0; --i) {
        sift_down(first, i - 1, n, comp);
    }

    for (std::size_t heap_size = n; heap_size > 1; --heap_size) {
        std::iter_swap(first, first + heap_size - 1);
        sift_down(first, 0, heap_size - 1, comp);
    }
}

template <typename Iterator, typename Compare>
void sort_checked(Iterator first, Iterator last, Compare comp) {
    using category = typename std::iterator_traits<Iterator>::iterator_category;
    static_assert(std::is_base_of_v<std::random_access_iterator_tag, category>,
                  "sort_checked needs random access iterators");

    simple_sort(first, last, comp);
}

template <typename Container, typename T, typename = void>
struct has_stack_interface : std::false_type {
};

template <typename Container, typename T>
struct has_stack_interface<Container,
                           T,
                           std::void_t<
                               decltype(std::declval<Container&>().push_back(std::declval<T>())),
                               decltype(std::declval<Container&>().pop_back()),
                               decltype(std::declval<Container&>().back()),
                               decltype(std::declval<const Container&>().size()),
                               decltype(std::declval<const Container&>().empty())>> : std::true_type {
};

template <typename T, typename Container = std::deque<T>>
class CheckedStack {
    static_assert(has_stack_interface<Container, T>::value,
                  "Container does not match stack static interface");

private:
    Container data;

public:
    void push(const T& value) {
        data.push_back(value);
    }

    void pop() {
        if (!data.empty()) {
            data.pop_back();
        }
    }

    T& top() {
        return data.back();
    }

    const T& top() const {
        return data.back();
    }

    std::size_t length() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }
};

// void demo_bad() {
//     std::list<int> bad = {3, 2, 1};
//     sort_checked(bad.begin(), bad.end(), [](int a, int b) {
//         return a < b;
//     });

//     CheckedStack<int, std::forward_list<int>> bad_stack;
//     bad_stack.push(1);
// }


int main() {
    std::vector<int> v = {5, 1, 4, 2, 3};
    sort_checked(v.begin(), v.end(), [](int a, int b) {
        return a < b;
    });

    std::cout << "sorted: ";
    for (int x : v) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    CheckedStack<int> st;
    st.push(10);
    st.push(20);
    st.push(30);

    std::cout << "stack top: " << st.top() << '\n';
    std::cout << "stack length: " << st.length() << '\n';

    // demo_bad();

    return 0;
}