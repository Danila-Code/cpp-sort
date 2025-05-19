#include <vector>
#include "sort.h"
#include "tests.h"
#include "log_duration.h"

int main() {
    using namespace sort;
    using namespace tests;
    
    TestSorting();

    const size_t size = 10000;
    std::vector<int> vec = tests::detail::FillVector(size);

    CompareSortingType(vec.begin(), vec.end(), std::less<int>());

    return 0;
}