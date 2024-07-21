#include "kdtree.hpp"

#include <iostream>

int main() {
    KDTree<std::tuple<int>, int> tree;

    for (auto& item: tree) {
        std::cout << item.second << std::endl;
    }

    return 0;
}
