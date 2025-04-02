#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5}; // Uses C++11 list initialization
    for (const auto& num : numbers) { // Uses C++11 range-based loop
        std::cout << num << " ";
    }
    return 0;
}