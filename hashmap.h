#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <functional>
#include <vector>
#include <utility>

template <typename K, typename V> // template used to use the same code for input types, hopefully this wouldnt be considered outside the rules, just used to shorten the code
class HashMap {
    int capacity;
    int size;
    std::vector<std::vector<std::pair<K, V>>> table;

    int hash(const int& key){ // for int key
        return key % capacity;
    }
    int hash(const std::string& key){ // for string key, I dont take any other type of keys except int and string so only two hashes
        int h = 0;
        for (char c : key) {
            h = (h * 31 + c) % capacity; // polynomial roll hash
        }
        return h;
    }



public:
    HashMap(int cap = 10000) : capacity(cap), size(0), table(cap){} //refer README for max size allowed for files
    ~HashMap() = default;

    void insert(const K& key, const V& value) {
        int idx = hash(key);
        table[idx].push_back({key, value});
        size++;
    }

    V get(const K& key) {
        int idx = hash(key);
        for (auto& target : table[idx]) {
            V value;
            if (target.first == key) {
                value = target.second;
                return value;
            }
        }
        return nullptr;
    }

    V remove(const K& key) {
        int idx = hash(key);
        auto& target = table[idx];
        for (auto it = target.begin(); it != target.end(); it++) {
            if (it->first == key) {
                V value = it->second;
                size--;
                table[idx].erase(it);
                return value;
            }
        }
        return nullptr;
    }

    int getSize() const { return size; }
};

#endif
