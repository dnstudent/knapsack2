//
// Created by Davide Nicoli on 17/05/21.
//

#ifndef KNAPSACK_DYNAMIC_HPP
#define KNAPSACK_DYNAMIC_HPP

#include <iostream>
#include <iterator>
#include <optional>
#include <tuple>
#include <vector>

#include "../definitions.hpp"
#include "../utilities.hpp"
#include "recursive.hpp"

namespace knapsack::simple::dynamic {
    template<typename Value>
    Value best_value_space(const size_t capacity, const knapsack::Items<Value, size_t> &items) {
        if (items.size() == 0) return 0;
        using cache_vec = typename knapsack::Cache<Value>::value_type;
        knapsack::Cache<Value> m(2, cache_vec(capacity + 1));
        knapsack::fill_cache_vec(m[0].begin(), capacity, items.values[0], items.weights[0]);
        //std::cout << m[1][34] << std::endl;
        for (auto partial_index = 1; partial_index < items.size(); ++partial_index) {
            for (size_t partial_capacity = 1; partial_capacity <= capacity; ++partial_capacity) {
                auto i = partial_index % 2;
                if (size_t item_weight = items.weights[partial_index];
                        item_weight <= partial_capacity) {
                    m[i][partial_capacity] = std::max(m[1 - i][partial_capacity - item_weight]
                                                      + items.values[partial_index], m[1 - i][partial_capacity]);
                } else {
                    m[i][partial_capacity] = m[1 - i][partial_capacity];
                }
            }
        }
        return m[(items.size() + 1) % 2][capacity];
    }

    // First row must be populated
    template<typename Value>
    Value _coc_best_value(const size_t free_space,
                          const size_t i,
                          const knapsack::Items<Value, size_t> &items,
                          knapsack::OptCache<Value> &m) {
        if (m[i][free_space].has_value()) {
            return m[i][free_space].value();
        }
        if (auto item_weight = items.weights[i]; free_space >= item_weight) {
            Value with_item = _coc_best_value(free_space - item_weight, i - 1, items, m) + items.values[i];
            Value without_item = _coc_best_value(free_space, i - 1, items, m);
            m[i][free_space] = std::max(with_item, without_item);
        } else {
            m[i][free_space] = _coc_best_value(free_space, i - 1, items, m);
        }
        return m[i][free_space].value();
    }

    template<typename Value>
    Value best_value_cycles(const size_t capacity, const knapsack::Items<Value, size_t> &items) {
        if (items.size() == 0) return 0;
        using cache_vec = typename knapsack::OptCache<Value>::value_type;
        knapsack::OptCache<Value> m(items.size());
        m[0] = cache_vec(capacity + 1);
        knapsack::fill_cache_vec(m[0].begin(), capacity, items.values[0], items.weights[0]);
        std::fill(std::next(m.begin()), m.end(), cache_vec(capacity + 1, std::optional<Value>()));

        return _coc_best_value(capacity, items.size() - 1, items, m);
    }
}

#endif //KNAPSACK_DYNAMIC_HPP
