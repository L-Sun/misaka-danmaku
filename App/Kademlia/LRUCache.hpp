#pragma once
#include <unordered_map>
#include <list>
#include <optional>

namespace Misaka::Kademlia {

template <typename Key, typename Value, size_t Size>
class LRUCache {
    using Node = typename std::pair<Key, Value>;
    using Iter = typename std::list<Node>::iterator;

public:
    void Add(Key key, Value val) {
        if (m_Map.count(key) != 0) {
            MakeRecently(key);
            m_Cache.front().second = std::move(val);
        } else {
            if (m_Map.size() == Size) RemoveLeastRecently();

            m_Cache.emplace_front(key, std::move(val));
            m_Map.emplace(std::move(key), m_Cache.begin());
        }
    }

    std::optional<const std::reference_wrapper<Value>> Get(const Key& key) {
        if (m_Map.count(key) == 0) return std::nullopt;

        MakeRecently(key);
        return m_Cache.front().second;
    }

    bool Full() const noexcept { return m_Map.size() == Size; }

    auto begin() const noexcept { return m_Cache.cbegin(); }
    auto end() const noexcept { return m_Cache.cend(); }

private:
    void MakeRecently(const Key& key) {
        m_Cache.splice(m_Cache.cbegin(), m_Cache, m_Map.at(key));
    }
    void RemoveLeastRecently() {
        m_Map.erase(m_Cache.back().first);
        m_Cache.pop_back();
    }

    // 1 <-> 2 <-> 3 <-> 4
    // ^
    // |
    // Recently used
    std::list<Node>               m_Cache;
    std::unordered_map<Key, Iter> m_Map;
};

}  // namespace Misaka::Kademlia