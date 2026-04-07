#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <random>
#include <iterator>

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
void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
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

bool less_int(int a, int b) {
    return a < b;
}

struct GreaterInt {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

template <typename Container>
void print_container(const Container& c) {
    for (const auto& x : c) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

void demo_sort() {
    std::vector<int> v1 = {5, 2, 9, 1, 3};
    ::sort(v1.begin(), v1.end(), less_int);
    std::cout << "vector function: ";
    print_container(v1);

    std::deque<int> d1 = {5, 2, 9, 1, 3};
    ::sort(d1.begin(), d1.end(), [](int a, int b) {
        return a < b;
    });
    std::cout << "deque lambda: ";
    print_container(d1);

    std::vector<int> v2 = {5, 2, 9, 1, 3};
    ::sort(v2.begin(), v2.end(), GreaterInt{});
    std::cout << "vector functor: ";
    print_container(v2);
}

template <typename Container>
long long benchmark(Container c) {
    auto start = std::chrono::steady_clock::now();
    ::sort(c.begin(), c.end(), [](int a, int b) {
        return a < b;
    });
    auto end = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void benchmark_test() {
    const int N = 500000;

    std::vector<int> data;
    data.reserve(N);

    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(-1000000, 1000000);

    for (int i = 0; i < N; ++i) {
        data.push_back(dist(gen));
    }

    std::vector<int> v(data.begin(), data.end());
    std::deque<int> d(data.begin(), data.end());

    long long t1 = benchmark(v);
    long long t2 = benchmark(d);

    std::cout << "vector ms: " << t1 << '\n';
    std::cout << "deque ms: " << t2 << '\n';

    if (t1 < t2) {
        std::cout << "faster: vector\n";
    } else {
        std::cout << "faster: deque\n";
    }
}

int main() {
    demo_sort();
    benchmark_test();
    return 0;
}