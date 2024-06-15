#ifndef VE281P1_SORT_HPP
#define VE281P1_SORT_HPP

#include <functional>
#include <stdlib.h>
#include <vector>

template<typename T, typename Compare>
void bubble_sort(std::vector<T>& vector, Compare comp = std::less<T>()) {
    for (int i = 0; i < static_cast<int>(vector.size()); i++) {
        bool flag = false;
        for (int j = 0; j < static_cast<int>(vector.size()) - i - 1; j++) {
            if (comp(vector[j + 1], vector[j])) {
                std::swap(vector[j], vector[j + 1]);
                flag = true;
            }
        }
        if (!flag) {
            break;
        }
    }
}

template<typename T, typename Compare>
void insertion_sort(std::vector<T>& vector, Compare comp = std::less<T>()) {
    for (int i = 1; i < static_cast<int>(vector.size()); i++) {
        T key = vector[i];
        int j = i - 1;
        while (j >= 0 && comp(key, vector[j])) {
            vector[j + 1] = vector[j];
            j--;
        }
        vector[j + 1] = key;
    }
}

template<typename T, typename Compare>
void selection_sort(std::vector<T>& vector, Compare comp = std::less<T>()) {
    int left = 0;
    int right = static_cast<int>(vector.size() - 1);

    while (left < right) {
        int min_index = left;
        int max_index = right;

        for (int i = left; i <= right; ++i) {
            if (comp(vector[i], vector[min_index])) {
                min_index = i;
            }
            if (comp(vector[max_index], vector[i])) {
                max_index = i;
            }
        }

        std::swap(vector[left], vector[min_index]);
        if (max_index == left) {
            max_index = min_index;
        }
        std::swap(vector[right], vector[max_index]);

        ++left;
        --right;
    }
}

template<typename T, typename Compare>
void merge(std::vector<T>& vector, int l, int m, int r, Compare comp = std::less<T>()) {
    int n_l = m - l + 1;
    int n_r = r - m;
    std::vector<T> left(n_l);
    std::vector<T> right(n_r);
    for (int i = 0; i < n_l; i++) {
        left[i] = vector[l + i];
    }
    for (int i = 0; i < n_r; i++) {
        right[i] = vector[m + 1 + i];
    }
    int i = 0;
    int j = 0;
    int k = l;
    while (i < n_l && j < n_r) {
        if (!comp(right[j], left[i])) {
            vector[k] = left[i];
            i++;
        } else {
            vector[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n_l) {
        vector[k] = left[i];
        i++;
        k++;
    }
    while (j < n_r) {
        vector[k] = right[j];
        j++;
        k++;
    }
}

template<typename T, typename Compare>
void merge_sort(std::vector<T>& vector, Compare comp = std::less<T>()) {
    int n = static_cast<int>(vector.size());
    for (int curr_size = 1; curr_size <= n - 1; curr_size *= 2) {
        for (int l = 0; l < n - 1; l += 2 * curr_size) {
            int m = std::min(l + curr_size - 1, n - 1);
            int r = std::min(l + 2 * curr_size - 1, n - 1);
            merge(vector, l, m, r, comp);
        }
    }
}

template<typename T, typename Compare>
void quick_sort_extra(std::vector<T>& vector, Compare comp = std::less<T>()) {
    if (vector.size() <= 1) {
        return;
    }
    std::vector<T> left;
    std::vector<T> right;
    T pivot = vector[0];
    for (int i = 1; i < (int)vector.size(); i++) {
        if (comp(vector[i], pivot)) {
            left.push_back(vector[i]);
        } else {
            right.push_back(vector[i]);
        }
    }
    left.shrink_to_fit();
    right.shrink_to_fit();
    vector.clear();
    vector.shrink_to_fit();
    quick_sort_extra(left, comp);
    quick_sort_extra(right, comp);
    vector.insert(vector.end(), left.begin(), left.end());
    vector.push_back(pivot);
    vector.insert(vector.end(), right.begin(), right.end());
    vector.shrink_to_fit();
}

template<typename T, typename Compare>
int partition_inplace(std::vector<T>& vector, int low, int high, Compare comp = std::less<T>()) {
    T pivot = vector[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        // If current element is smaller than the pivot, swap the current element with the element at index i + 1
        if (comp(vector[j], pivot)) {
            i++;
            std::swap(vector[i], vector[j]);
        }
    }
    std::swap(vector[i + 1], vector[high]);
    return i + 1;
}

template<typename T, typename Compare>
void quick_sort_inplace_helper(
    std::vector<T>& vector,
    int low,
    int high,
    Compare comp = std::less<T>()
) {
    if (low < high) {
        int pi = partition_inplace(vector, low, high, comp);
        quick_sort_inplace_helper(vector, low, pi - 1, comp);
        quick_sort_inplace_helper(vector, pi + 1, high, comp);
    }
}

template<typename T, typename Compare>
void quick_sort_inplace(std::vector<T>& vector, Compare comp = std::less<T>()) {
    quick_sort_inplace_helper(vector, 0, static_cast<int>(vector.size()) - 1, comp);
}

#endif // VE281P1_SORT_HPP