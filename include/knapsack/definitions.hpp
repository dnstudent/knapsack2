//
// Created by Davide Nicoli on 17/05/21.
//

#ifndef KNAPSACK_DEFINITIONS_HPP
#define KNAPSACK_DEFINITIONS_HPP

#include <vector>

namespace knapsack {
    template<typename Value, typename Weight>
    struct Items {
        std::vector<Value> values;
        std::vector<Weight> weights;
    };
}

#endif //KNAPSACK_DEFINITIONS_HPP
