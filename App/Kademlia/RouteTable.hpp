#pragma once
#include "Kademlia.hpp"

#include <array>

namespace Misaka::Kademlia {

template <typename T>
class RouteTable {
public:
    RouteTable(ID id) : m_ID(std::move(id)) {}
    void Add(ID id, T val) {
        auto dis = cpl(m_ID, id);
        m_Buckets.at(dis).Add(std::move(id), std::move(val));
    }

    auto Get(const ID& id) const {
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
