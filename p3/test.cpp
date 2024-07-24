#include "kdtree.hpp"

#include <iostream>

int main() {
    KDTree<std::tuple<int, int>, int> tree;
    tree.insert(std::make_tuple(1, 2), 3);
    tree.insert(std::make_tuple(2, 3), 4);

    for (auto& [point, value] : tree) {
        std::cout << "Point: (" << std::get<0>(point) << ", " << std::get<1>(point) << "), Value: " << value << std::endl;
    }

    return 0;
}
