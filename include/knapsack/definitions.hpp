//
// Created by Davide Nicoli on 17/05/21.
//

#ifndef KNAPSACK_DEFINITIONS_HPP
#define KNAPSACK_DEFINITIONS_HPP

#include <optional>
#include <vector>

namespace knapsack {
    template<typename Value, typename Weight>
    struct Items {
        std::vector<Value> values;
        std::vector<Weight> weights;

        size_t size() const {
            return values.size();
        }
    };

    template<typename Value>
    using Cache = std::vector<std::vector<Value>>;

    template<typename Value>
    using OptCache = std::vector<std::vector<std::optional<Value>>>;
}

#endif //KNAPSACK_DEFINITIONS_HPP
