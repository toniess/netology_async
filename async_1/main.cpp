#include <iostream>
#include <vector>
#include <future>


int findMinIndex(const std::vector<int>& v, int start) {
    int min = start;
    for (int i = start; i < v.size(); ++i)
        if (v[i] < v[min])
            min = i;
    return min;
}


void sort(std::vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
        auto ft_minIndex = std::async(findMinIndex, std::ref(v), i);
        std::swap(v[i], v[ft_minIndex.get()]);
    }
}


int main() {
    std::vector<int> v = {3, 6, 3, 2, 6, 2, 83, 32, 1};
    sort(v);

    for (auto item : v)
        std::cout << item << " ";
    std::cout << "\n";
}
