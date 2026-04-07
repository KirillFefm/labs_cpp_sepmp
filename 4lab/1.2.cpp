#include <iostream>
#include <deque>
#include <string>

template <typename T, typename Container = std::deque<T>>
class Stack {
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

template <>
class Stack<char, std::string> {
private:
    std::string data;

public:
    void push(char value) {
        data.push_back(value);
    }

    void pop() {
        if (!data.empty()) {
            data.pop_back();
        }
    }

    char& top() {
        return data.back();
    }

    const char& top() const {
        return data.back();
    }

    std::size_t length() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }
};

int main() {
    Stack<int> numbers;
    numbers.push(10);
    numbers.push(20);
    numbers.push(30);

    std::cout << "int top: " << numbers.top() << '\n';
    numbers.pop();
    std::cout << "int length: " << numbers.length() << '\n';
    std::cout << "int empty: " << (numbers.empty() ? "yes" : "no") << '\n';

    Stack<char, std::string> letters;
    letters.push('a');
    letters.push('b');
    letters.push('c');

    std::cout << "char top: " << letters.top() << '\n';
    letters.pop();
    std::cout << "char length: " << letters.length() << '\n';
    std::cout << "char empty: " << (letters.empty() ? "yes" : "no") << '\n';

    return 0;
}