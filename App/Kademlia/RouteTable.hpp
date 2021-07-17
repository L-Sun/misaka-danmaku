#pragma once
#include "LRUCache.hpp"

#include "utils.hpp"

#include <array>
#include <bitset>

namespace Misaka::Kademlia {

constexpr size_t BucketSize = 20;
constexpr size_t IDsize     = 160;

using ID = std::bitset<IDsize>;

template <typename T>
class RouteTable {
public:
    RouteTable(ID id) : m_ID(id) {}

    auto GetID() const noexcept { return m_ID; }

    void Add(ID id, T val) {
        auto dis = cpl(m_ID, id);
        m_Buckets.at(dis).Add(id, val);
    }

    auto& GetBuckets(const ID& id) {
        auto dis = cpl(m_ID, id);
        return m_Buckets.at(dis);
    }

    bool Full() const noexcept {
        for (auto&& bucket : m_Buckets)
            if (!bucket.Full()) return false;

        return true;
    }

private:
    const ID                                        m_ID;
    std::array<LRUCache<ID, T, BucketSize>, IDsize> m_Buckets;
};

}  // namespace Misaka::Kademlia
