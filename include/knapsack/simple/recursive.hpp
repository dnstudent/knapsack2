//
// Created by Davide Nicoli on 17/05/21.
//

#ifndef KNAPSACK_RECURSIVE_HPP
#define KNAPSACK_RECURSIVE_HPP

#include <algorithm>
#include "../definitions.hpp"

namespace knapsack::simple::recursive {
    template<typename Value, typename Weight>
    Value best_value(const Weight free_space,
                     const Value cumulative_value,
                     const size_t i,
                     const knapsack::Items<Value, Weight> &items) {
        if (i >= items.values.size())
            return cumulative_value;
        // Weight could be unsigned
        if (Weight item_weight = items.weights[i]; free_space >= item_weight) {
            Value with_item = best_value(free_space - item_weight,
                                         cumulative_value + items.values[i],
                                         i + 1,
                                         items);
            Value without_item = best_value(free_space, cumulative_value, i + 1, items);
            return std::max(with_item, without_item);
        }
        return best_value(free_space, cumulative_value, i + 1, items);
    }

    template<typename Value, typename Weight>
    Value best_value(const Weight capacity, const knapsack::Items<Value, Weight> &items) {
        return best_value(capacity, static_cast<Value>(0), 0, items);
    }
}

#endif //KNAPSACK_RECURSIVE_HPP
