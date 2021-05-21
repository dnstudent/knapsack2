#include <algorithm>
#include <random>
#include <vector>
#include <utility>

#include <benchmark/benchmark.h>

#include <knapsack/simple/recursive.hpp>
#include <knapsack/simple/dynamic.hpp>
#include <knapsack/definitions.hpp>

using Value = uint;
using Weight = size_t;
using Items = knapsack::Items<Value, Weight>;

void populate_items(Items &items) {
    std::default_random_engine gen;
    std::uniform_int_distribution<Value> r_value(0, 100);
    std::generate(items.values.begin(), items.values.end(), [&]() {return r_value(gen);});
    std::uniform_int_distribution<Weight> r_weight(0, 100);
    std::generate(items.weights.begin(), items.weights.end(), [&]() {return r_weight(gen);});
}

static void BM_recursive_best_value(benchmark::State &state) {
    state.PauseTiming();
    const size_t N = state.range(0);
    Items items{std::vector<Value>(N), std::vector<Weight>(N)};
    state.ResumeTiming();
    for (auto _ : state) {
        state.PauseTiming();
        populate_items(items);
        state.ResumeTiming();
        knapsack::simple::recursive::best_value(static_cast<Weight>(state.range(1)), items);
    }
}

static void BM_dynamic_best_value_space(benchmark::State &state) {
    state.PauseTiming();
    const size_t N = state.range(0);
    Items items{std::vector<Value>(N), std::vector<size_t>(N)};
    state.ResumeTiming();
    for (auto _ : state) {
        state.PauseTiming();
        populate_items(items);
        state.ResumeTiming();
        knapsack::simple::dynamic::best_value_space(state.range(1), items);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_dynamic_best_value_cycles(benchmark::State &state) {
    state.PauseTiming();
    const size_t N = state.range(0);
    Items items{std::vector<Value>(N), std::vector<size_t>(N)};
    state.ResumeTiming();
    for (auto _ : state) {
        state.PauseTiming();
        populate_items(items);
        state.ResumeTiming();
        knapsack::simple::dynamic::best_value_cycles(state.range(1), items);
    }
    state.SetComplexityN(state.range(0));
}

static void FullChain(benchmark::internal::Benchmark *b) {
    for (int i = 3; i <= 20; ++i)
        b->Args({1 << i, 5000});
}

static void ShortChain(benchmark::internal::Benchmark *b) {
    for (int i = 3; i <= 10; ++i)
        b->Args({1 << i, 50 * (1 << i)});
}

static void FixedCap(benchmark::internal::Benchmark *b) {
    for (int i = 15; i <= 20; ++i)
        b->Args({1 << i, 50});
}

// BENCHMARK(BM_recursive_best_value)->Apply(ShortChain);
// BENCHMARK(BM_dynamic_best_value_space)->Apply(ShortChain);
BENCHMARK(BM_dynamic_best_value_space)->Apply(FullChain)->Complexity();
BENCHMARK(BM_dynamic_best_value_cycles)->Apply(FixedCap)->Complexity();

BENCHMARK_MAIN();
