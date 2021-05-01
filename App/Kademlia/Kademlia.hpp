#pragma once
#include <bitset>

namespace Misaka::Kademlia {
constexpr size_t BucketSize = 20;
constexpr size_t IDsize     = 160;

using ID = std::bitset<IDsize>;

template <size_t N>
size_t cpl(const std::bitset<N>& id1, const std::bitset<N>& id2) {
    std::bitset dis = id1 ^ id2;
    size_t      len = 0;
    while (len < N && !dis.test(N - 1 - len)) {
        len++;
    }
    return len;
}
}  // namespace Misaka::Kademlia

#include "LRUCache.hpp"
#include "RouteTable.hpp"