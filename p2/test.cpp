#include <iostream>

#include "hashtable.hpp"

template<typename T, typename U>
void contains_key(HashTable<T, U>& hash_table, const T& key) {
    if (hash_table.contains(key)) {
        std::cout << "Key: " << key << " found with value: " << hash_table[key] << std::endl;
    } else {
        std::cout << "Key: " << key << " not found" << std::endl;
    }
}

template<typename T, typename U>
void find_key(HashTable<T, U>& hash_table, const T& key) {
    auto it = hash_table.find(key);
    if (it != hash_table.end()) {
        std::cout << "Key: " << key << " found with value: " << it->second << std::endl;
    } else {
        std::cout << "Key: " << key << " not found" << std::endl;
    }
}

template<typename T, typename U>
void print_hash_table(HashTable<T, U>& hash_table) {
    std::cout << "========== Resulting HashTable ==========" << std::endl;
    for (auto& [key, value]: hash_table) {
        std::cout << "Key: " << key << " Value: " << value << std::endl;
    }
    std::cout << "=========================================" << std::endl;
}

int main() {
    HashTable<int, int> hash_table;
    hash_table.insert(27, 64);
    hash_table.insert(824, 426);
    contains_key(hash_table, 27);
    print_hash_table(hash_table);
    hash_table.erase(27);
    find_key(hash_table, 27);
    hash_table.rehash(10);
    find_key(hash_table, 824);
    print_hash_table(hash_table);

    return 0;
}
