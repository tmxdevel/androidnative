#ifndef NATIVEANDROID_CHASHMAP_H
#define NATIVEANDROID_CHASHMAP_H

#include <map>
#include <vector>

template<class K, class V>
class CHashMap
{
public:
    void put(K key, V value);
    V get(K key, V defValue) const;
    std::vector<K> keys() const;
    std::vector<V> values() const;
    bool contains(V value) const;
    bool containsKey(K key) const;
    int size() const;
    void forEach(void f(K key, V val));

private:
    std::map<K, V> _map;
};

template<class K, class V>
void CHashMap<K, V>::put(K key, V value) {
    _map.insert(std::pair<K, V>(key, value));
}

template<class K, class V>
V CHashMap<K, V>::get(K key, V defValue) const {
    auto result = _map.find(key);
    if(result == _map.end()) return defValue;
    return result->second;
}

template<class K, class V>
std::vector<K> CHashMap<K, V>::keys() const {
    std::vector<K> keys(_map.size());
    for(auto entry : _map) {
        keys.push_back(entry.first);
    }
    return keys;
}

template<class K, class V>
std::vector<V> CHashMap<K, V>::values() const {
    std::vector<V> values(_map.size());
    for(auto entry : _map) {
        values.push_back(entry.second);
    }
    return values;
}

template<class K, class V>
bool CHashMap<K, V>::contains(V value) const {
    for(auto entry : _map) {
        if(entry.second == value) return true;
    }
    return false;
}

template<class K, class V>
bool CHashMap<K, V>::containsKey(K key) const {
    for(auto entry : _map) {
        if(entry.first == key) return true;
    }
    return false;
}

template<class K, class V>
int CHashMap<K, V>::size() const {
    return _map.size();
}

template<class K, class V>
void CHashMap<K, V>::forEach(void (*f)(K, V)) {
    for(auto entry : _map) {
        f(entry.first, entry->second);
    }
}

#endif //NATIVEANDROID_CHASHMAP_H
