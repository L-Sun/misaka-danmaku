#pragma once
#include "LRUCache.hpp"

#include "utils.hpp"

#include <vector>
#include <bitset>

namespace Misaka::Kademlia {

constexpr size_t BucketSize = 20;
constexpr size_t IDsize     = 160;

using ID = std::bitset<IDsize>;

template <typename T>
class RouteTable {
public:
    RouteTable(ID id) : m_ID(id), m_Buckets(1) {}

    auto GetID() const noexcept { return m_ID; }

    void Add(ID id, T val) {
        auto dis = cpl(m_ID, id);

        if (dis >= m_Buckets.size() - 1 && m_Buckets.back().Full()) {
            SplitUngroupedBucket();
        }

        m_Buckets.at(std::min(dis, m_Buckets.size() - 1)).Add(id, val);
    }

    auto& GetBucket(const ID& id) {
        auto dis = cpl(m_ID, id);
        return m_Buckets.at(std::min(dis, m_Buckets.size() - 1));
    }

    bool Full() const noexcept {
        for (auto&& bucket : m_Buckets)
            if (!bucket.Full()) return false;

        return true;
    }

private:
    void SplitUngroupedBucket() {
        std::vector<ID> marker;
        for (auto&& [id, val] : m_Buckets.back()) {
            if (cpl(id, m_ID) >= m_Buckets.size()) {
                marker.emplace_back(id);
            }
        }
        auto& new_ungrouped_bucket = m_Buckets.emplace_back();
        auto& old_ungrouped_bucket = m_Buckets.at(m_Buckets.size() - 2);
        for (auto&& id : marker) {
            new_ungrouped_bucket.Add(id, old_ungrouped_bucket.Remove(id));
        }
    }

    const ID                                 m_ID;
    std::vector<LRUCache<ID, T, BucketSize>> m_Buckets;
};

}  // namespace Misaka::Kademlia
