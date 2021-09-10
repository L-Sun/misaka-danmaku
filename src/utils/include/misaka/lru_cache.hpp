#pragma once
#include <unordered_map>
#include <list>
#include <optional>

namespace misaka {

template <typename Key, typename Value, size_t Capacity>
class lru_cache {
    using Node = typename std::pair<Key, Value>;
    using Iter = typename std::list<Node>::iterator;

public:
    lru_cache() = default;
    lru_cache(const lru_cache& rhs) : m_Cache(rhs.m_Cache) {
        ReMap();
    }
    lru_cache& operator=(const lru_cache& rhs) {
        m_Cache = rhs.m_Cache;
        ReMap();
        return *this;
    };

    void Add(Key key, Value val) {
        if (m_Map.count(key) != 0) {
            MakeRecently(key);
            m_Cache.front().second = std::move(val);
        } else {
            if (Full()) RemoveLeastRecently();

            m_Cache.emplace_front(key, std::move(val));
            m_Map.emplace(std::move(key), m_Cache.begin());
        }
    }

    Value Remove(Key key) {
        Iter  iter   = m_Map.at(key);
        Value result = std::move(iter->second);
        m_Cache.erase(iter);
        m_Map.erase(key);
        return result;
    }

    std::optional<const std::reference_wrapper<Value>> Get(const Key& key) {
        if (m_Map.count(key) == 0) return std::nullopt;

        MakeRecently(key);
        return m_Cache.front().second;
    }

    bool Full() const noexcept { return m_Map.size() == Capacity; }

    size_t Size() const noexcept { return m_Cache.size(); }

    auto begin() const noexcept { return m_Cache.cbegin(); }
    auto end() const noexcept { return m_Cache.cend(); }

private:
    void MakeRecently(const Key& key) {
        m_Cache.splice(m_Cache.begin(), m_Cache, m_Map.at(key));
    }
    void RemoveLeastRecently() {
        m_Map.erase(m_Cache.back().first);
        m_Cache.pop_back();
    }
    void ReMap() {
        m_Map.clear();
        for (auto iter = m_Cache.begin(); iter != m_Cache.end(); iter++) {
            m_Map.emplace(iter->first, iter);
        }
    }

    // 1 <-> 2 <-> 3 <-> 4
    // ^
    // |
    // Recently used
    std::list<Node>               m_Cache;
    std::unordered_map<Key, Iter> m_Map;
};

}  // namespace misaka