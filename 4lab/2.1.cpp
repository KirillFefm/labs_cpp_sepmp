#include <iostream>
#include <tuple>
#include <string>

template <std::size_t Index, typename Tuple>
struct TupleWalker {
    template <typename UnaryOp>
    static void apply(const Tuple& t, UnaryOp op) {
        op(std::get<Index>(t));
        TupleWalker<Index + 1, Tuple>::apply(t, op);
    }
};

template <typename Tuple>
struct TupleWalker<std::tuple_size<Tuple>::value, Tuple> {
    template <typename UnaryOp>
    static void apply(const Tuple&, UnaryOp) {
    }
};

template <typename... Args, typename UnaryOp>
void tuple_for_each(const std::tuple<Args...>& t, UnaryOp op) {
    TupleWalker<0, std::tuple<Args...>>::apply(t, op);
}

int main() {
    auto mixed = std::make_tuple(10, 2.5, std::string("hello"), 'X');
    std::cout << "tuple values: ";
    tuple_for_each(mixed, [](const auto& value) {
        std::cout << value << ' ';
    });
    std::cout << '\n';

    std::tuple<int, int, int, int> nums = {1, 2, 3, 4};
    int sum = 0;
    tuple_for_each(nums, [&sum](int value) {
        sum += value;
    });
    std::cout << "sum: " << sum << '\n';

    return 0;
}