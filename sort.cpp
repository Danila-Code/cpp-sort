#include "sort.h"
#include <string>

namespace sort {
namespace detail {
std::string ToString(SortType type) {
    using namespace std::literals;
    switch(type) {
        case SortType::QUICK_SORT:
        return "Quick sort"s;
        break;
        case SortType::BUBBLE_SORT:
        return "Bubble sort"s;
        break;
        case SortType::CHOICE_SORT:
        return "Sort by choice"s;
        break;
        case SortType::INSERT_SORT:
        return "Sort by inserts"s;
    }
    return {};
}
}// namespace detail
}// namespace sort