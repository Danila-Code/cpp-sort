#include <iostream>
#include <cassert>
#include <vector>
#include <random>
#include "sort.h"

namespace tests {

namespace detail {
std::vector<int> FillVector(size_t size) {
    std::vector<int> result;
    result.reserve(size);

    std::random_device r;
    std::mt19937 rand_gen(r());

    for(size_t i = 0; i < size; ++i) {
        result.push_back(rand_gen()%size);
    }
    
    return result;
}
}// namespace detail

void TestSorting() {
    using namespace sort;
    using namespace sort::functions;
    using namespace detail;

    const size_t size = 100;
    std::vector<int> vec = FillVector(size);
    std::vector<int> sorted_vec = vec;

    auto comp = [](int lhs, int rhs) {
        return lhs < rhs;
    };

    std::sort(sorted_vec.begin(), sorted_vec.end(), comp);

    {
        std::vector<int> sort_vector = vec;
        BubbleSort(sort_vector.begin(), sort_vector.end(), comp);

        assert(sort_vector == sorted_vec);
    }
    {
        std::vector<int> sort_vector = vec;
        SortByInserts(sort_vector.begin(), sort_vector.end(), comp);
        
        assert(sort_vector == sorted_vec);
    }
    {
        std::vector<int> sort_vector = vec;
        SortingByChoice(sort_vector.begin(), sort_vector.end(), comp);
        
        assert(sort_vector == sorted_vec);
    }
    {
        std::vector<int> sort_vector = vec;
        QuickSort(sort_vector.begin(), sort_vector.end(), comp);
        
        assert(sort_vector == sorted_vec);
    }

    using namespace std::literals;
    std::cout << "Testing ...OK"s <<std::endl;
}

}// namespace tests