//
// Created by Davide Nicoli on 18/05/21.
//

#ifndef KNAPSACK_UTILITIES_HPP
#define KNAPSACK_UTILITIES_HPP

#include <algorithm>
#include <iterator>
#include <optional>

namespace knapsack {
    template<typename Value, typename Weight, typename It>
    void fill_cache_vec(const It begin, Weight capacity, Value value, Weight weight) {
        const auto filled_to = std::fill_n(begin,
                                           std::min(capacity, weight),
                                           static_cast<Value>(0));
        std::fill(filled_to, std::next(begin, capacity+1), static_cast<Value>(value));
    }
}

#endif //KNAPSACK_UTILITIES_HPP
