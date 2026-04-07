#include <array>
#include <tuple>
#include <iostream>
#include <type_traits>
#include <utility>

template <typename ArraysTuple, std::size_t... ValueIndices, std::size_t... ArrayIndices>
constexpr auto make_item_impl(const ArraysTuple& arrays,
                              std::index_sequence<ValueIndices...>,
                              std::index_sequence<ArrayIndices...>) {
    return std::make_tuple(std::get<ArrayIndices>(arrays)[ValueIndices]...);
}

template <typename ArraysTuple, std::size_t... ValueIndices>
constexpr auto make_item(const ArraysTuple& arrays, std::index_sequence<ValueIndices...>) {
    return make_item_impl(arrays,
                          std::index_sequence<ValueIndices...>{},
                          std::make_index_sequence<sizeof...(ValueIndices)>{});
}

template <std::size_t Dim, typename ArraysTuple, std::size_t... Chosen>
constexpr auto build_level(const ArraysTuple& arrays, std::index_sequence<Chosen...> chosen);

template <std::size_t Dim,
          typename ArraysTuple,
          std::size_t... Chosen,
          std::size_t... CurrentDimIndices>
constexpr auto build_array_impl(const ArraysTuple& arrays,
                                std::index_sequence<Chosen...>,
                                std::index_sequence<CurrentDimIndices...>) {
    return std::array{build_level<Dim + 1>(arrays,
                                           std::index_sequence<Chosen..., CurrentDimIndices>{})...};
}

template <std::size_t Dim, typename ArraysTuple, std::size_t... Chosen>
constexpr auto build_level(const ArraysTuple& arrays, std::index_sequence<Chosen...> chosen) {
    constexpr std::size_t dims = std::tuple_size_v<std::remove_reference_t<ArraysTuple>>;

    if constexpr (Dim == dims) {
        return make_item(arrays, chosen);
    } else {
        using CurrentArray = std::remove_reference_t<decltype(std::get<Dim>(arrays))>;
        constexpr std::size_t current_size = std::tuple_size_v<CurrentArray>;

        return build_array_impl<Dim>(arrays,
                                     chosen,
                                     std::make_index_sequence<current_size>{});
    }
}

template <typename... Arrays>
constexpr auto cartesian_product(const Arrays&... arrays) {
    static_assert(sizeof...(Arrays) > 0, "At least one array is required");
    auto arrays_tuple = std::tuple<const Arrays&...>(arrays...);
    return build_level<0>(arrays_tuple, std::index_sequence<>{});
}

int main() {
    constexpr std::array<int, 2> a1 = {1, 2};
    constexpr std::array<char, 3> a2 = {'A', 'B', 'C'};
    constexpr std::array<double, 2> a3 = {0.1, 0.2};

    constexpr auto product = cartesian_product(a1, a2, a3);

    static_assert(std::get<0>(product[0][0][0]) == 1);
    static_assert(std::get<1>(product[0][1][1]) == 'B');
    static_assert(std::get<2>(product[1][2][0]) == 0.1);

    const auto sample = product[1][2][1];
    std::cout << "sample: "
              << std::get<0>(sample) << ' '
              << std::get<1>(sample) << ' '
              << std::get<2>(sample) << '\n';

    return 0;
}