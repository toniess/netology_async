#include <iostream>
#include <vector>
#include <algorithm>
#include <future>


template <typename RandomIt, typename Func>
void parallel_for_each(RandomIt first, RandomIt last, Func f, std::size_t num_threads) {

    std::size_t distance = std::distance(first, last);
    if (distance <= 1000 || num_threads == 1) {
        std::for_each(first, last, f);
    } else {
        RandomIt middle = first;
        std::advance(middle, distance / 2);

        // Рекурсивно создаем задачи для левой и правой половин контейнера
        std::future<void> left = std::async(std::launch::async, [first, middle, &f, num_threads] {
            parallel_for_each(first, middle, f, num_threads / 2);
        });

        std::future<void> right = std::async(std::launch::async, [middle, last, &f, num_threads] {
            parallel_for_each(middle, last, f, num_threads / 2);
        });

        left.get();
        right.get();
    }
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Параллельно применяем функцию к каждому элементу вектора
    parallel_for_each(vec.begin(), vec.end(), [](int& n) {
            n *= 2;
        }, 4);

    // Выводим преобразованный массив
    std::cout << "Преобразованный массив: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
