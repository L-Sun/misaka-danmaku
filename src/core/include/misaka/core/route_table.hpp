#pragma once

#include <misaka/core/id.hpp>
#include <misaka/lru_cache.hpp>

#include <vector>

namespace misaka::core {
constexpr size_t BucketSize = 20;

template <typename T>
class RouteTable {
public:
    RouteTable(KadID id) : m_ID(id), m_Buckets(1) {}

    auto GetID() const noexcept { return m_ID; }

    void Add(KadID id, T val) {
        auto dis = cpl(m_ID, id);

        if (dis >= m_Buckets.size() - 1 && m_Buckets.back().Full()) {
            SplitUngroupedBucket();
        }

        m_Buckets.at(std::min(dis, m_Buckets.size() - 1)).Add(id, val);
    }

    auto& GetBucket(const KadID& id) {
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
        std::vector<KadID> marker;
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

    const KadID                                  m_ID;
    std::vector<lru_cache<KadID, T, BucketSize>> m_Buckets;
};

}  // namespace misaka::core
