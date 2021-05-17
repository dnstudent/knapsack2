#include <random>
#include <tuple>
#include <vector>

#include <gtest/gtest.h>
#include <knapsack/simple/recursive.hpp>

using Value = uint;
using Weight = uint;
using Items = knapsack::Items<Value, Weight>;

//static const std::vector<Items> items{
//    {{50, 56}, {50, 59}, {64, 80}, {46, 64}, {50, 75}, {5, 17}},
//    {{4, 12}, {2, 2}, {1, 1}, {2, 1}, {10, 4}},
//    {{60, 10}, {100, 20}, {120, 30}},
//    {{}}
//};

const std::vector<std::tuple<Items, Weight, Value>> testing_tuples{
        {{{50, 50,  64, 46, 50, 5}, {56, 59, 80, 64, 75, 17}}, 190, 150},
        {{{4,  2,   1,  2,  10},    {12, 2,  1,  1,  4}},      15,  15},
        {{{60, 100, 120},           {10, 20, 30}},             50,  220},
        {{{},                       {}},                       10,  0}
};

const Items testing_items{{1, 2, 3},
                          {4, 5, 6}};

TEST(SIMPLE, Recursive) {
    bool all = std::all_of(testing_tuples.begin(), testing_tuples.end(),
                   [](const auto tuple) {
                       return knapsack::simple::recursive::best_value(std::get<1>(tuple),
                                                                      std::get<0>(tuple)) == std::get<2>(tuple);
                   });
    ASSERT_TRUE(all);
}
