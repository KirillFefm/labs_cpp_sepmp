#include <array>
#include <cstddef>
#include <iostream>

template <std::size_t N, std::size_t Index>
struct LinearRecurrence {
    static constexpr long long value(const std::array<long long, N>& init,
                                     const std::array<long long, N>& coeff) {
        if constexpr (Index < N) {
            return init[Index];
        } else {
            return sum_terms<0>(init, coeff);
        }
    }

private:
    template <std::size_t I>
    static constexpr long long sum_terms(const std::array<long long, N>& init,
                                         const std::array<long long, N>& coeff) {
        if constexpr (I == N) {
            return 0;
        } else {
            return coeff[I] * LinearRecurrence<N, Index - N + I>::value(init, coeff)
                 + sum_terms<I + 1>(init, coeff);
        }
    }
};

template <std::size_t Index, std::size_t N>
constexpr long long recurrence_value(const std::array<long long, N>& init,
                                     const std::array<long long, N>& coeff) {
    return LinearRecurrence<N, Index>::value(init, coeff);
}

int main() {
    constexpr std::array<long long, 2> fib_init = {0, 1};
    constexpr std::array<long long, 2> fib_coeff = {1, 1};
    constexpr long long fib10 = recurrence_value<10>(fib_init, fib_coeff);
    static_assert(fib10 == 55);

    constexpr std::array<long long, 3> custom_init = {0, 1, 2};
    constexpr std::array<long long, 3> custom_coeff = {1, 1, 1};
    constexpr long long custom8 = recurrence_value<8>(custom_init, custom_coeff);

    std::cout << "fib(10): " << fib10 << '\n';
    std::cout << "custom(8): " << custom8 << '\n';

    return 0;
}