#pragma once

#include <bitset>
#include <random>

namespace misaka::core {
constexpr size_t IDsize = 160;
using KadID             = std::bitset<IDsize>;

// TODO use override function ^
template <size_t N>
size_t cpl(const std::bitset<N>& id1, const std::bitset<N>& id2) {
    std::bitset dis = id1 ^ id2;
    size_t      len = 0;
    while (len < N && !dis.test(N - 1 - len)) {
        len++;
    }
    return len;
}

template <size_t N = IDsize>
std::bitset<N> GenerateRandomID() {
    static thread_local std::mt19937_64 generator;
    std::bernoulli_distribution         distribution(0.5);

    std::bitset<N> result;
    for (size_t i = 0; i < N; i++)
        result[i] = distribution(generator);

    return result;
}

}  // namespace misaka::core