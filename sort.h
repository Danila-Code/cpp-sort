#pragma once

#include <algorithm>
#include <string>
#include <iterator>

#include <vector>

#include "log_duration.h"

#include <iostream>

namespace sort {

namespace functions{

// Quick sort, algorithm of Choar sorting
template <typename Iterator, typename Comparator>
void QuickSort(Iterator begin, Iterator end, Comparator comp) {
    size_t size = std::distance(begin, end);
    
    if(size < 2) {
        return;
    }

    Iterator pivot = begin;

    std::vector<typename std::iterator_traits<Iterator>::value_type> less_elements;
    std::vector<typename std::iterator_traits<Iterator>::value_type> greater_elements;

    for(Iterator iter = begin; iter != end; ++iter) {
        if(iter == pivot) {
            continue;
        }
        if(comp(*iter, *pivot)) {
            less_elements.push_back(*iter);
        } else {
            greater_elements.push_back(*iter);
        }
    }

    QuickSort(less_elements.begin(), less_elements.end(), comp);
    QuickSort(greater_elements.begin(), greater_elements.end(), comp);

    *(begin + less_elements.size()) = *pivot;
    for(Iterator iter = less_elements.begin(); iter != less_elements.end(); ++iter, ++begin) {
        *begin = *iter;
    }
    ++begin;
    for(Iterator iter = greater_elements.begin(); iter != greater_elements.end(); ++iter, ++begin) {
        *begin = *iter;
    }
}

// Bubble sorting
template <typename Iterator, typename Comparator>
void BubbleSort(Iterator begin, Iterator end, Comparator comp) {
    size_t size = std::distance(begin, end);

    if(size < 2) {
        return;
    }

    for(size_t i = 0; i < size; ++i) {
        bool isSorted = true;
        Iterator iter = begin;
        --end;
        while(iter != end) {
            if(!comp(*iter, *(iter+1))) {
                std::swap(*iter, *(iter+1));
                isSorted = false;
            }
            ++iter;
        }
        if(isSorted) {
            return;
        }
    }
}

// Sort by inserts
template <typename Iterator, typename Comparator>
void SortingByChoice(Iterator begin, Iterator end, Comparator comp) { 
    auto iter1 = begin;
    while(iter1 != (end - 1)) {
        auto target = iter1;
        auto iter2 = iter1 + 1;
        while(iter2 != end) {
            if(!comp(*target, *iter2)) {
               target = iter2;
            }
            ++iter2;
        }
        std::swap(*iter1, *target);
        ++iter1;
    }
}

// Sort by choice, unstable variant in place
template <typename Iterator, typename Comparator>
void SortByInserts(Iterator begin, Iterator end, Comparator comp) {
    auto iter1 = begin;
    while(iter1 != end) {
        auto target = iter1;

        auto iter2 = begin;
        while(iter2 != iter1) {
            if(comp(*iter1, *iter2)) {
                target = iter2;
                break;
            }
            ++iter2;
        }
        auto temp = *iter1;
        std::copy_backward(target, iter1, iter1 + 1);
        *target = temp;

        ++iter1;
    }
}

}// namespace functions

enum class SortType {
    QUICK_SORT,
    BUBBLE_SORT,
    INSERT_SORT,
    CHOICE_SORT
};

static const SortType all[] = {SortType::QUICK_SORT, SortType::BUBBLE_SORT,
     SortType::INSERT_SORT, SortType::CHOICE_SORT};

namespace detail {
std::string ToString(SortType type);
}// namespace detail

template <typename Iterator, typename Comparator>
void Sort(Iterator begin, Iterator end, Comparator comp,
    SortType sort_type = SortType::BUBBLE_SORT) {
    using namespace functions;
    
    switch (sort_type) {
        case SortType::QUICK_SORT:
        QuickSort(begin, end, comp);
        break;
        case SortType::BUBBLE_SORT:
        BubbleSort(begin, end, comp);
        break;
        case SortType::INSERT_SORT:
        SortByInserts(begin, end, comp);
        break;
        case SortType::CHOICE_SORT:
        SortingByChoice(begin, end, comp);
        break;
    }
}

template <typename Iterator, typename Comparator>
void CompareSortingType(Iterator begin, Iterator end, Comparator comp) {
    using namespace detail;

    for(SortType type : all) {
        std::vector<typename std::iterator_traits<Iterator>::value_type> test_vec{begin, end};
        LOG_DURATION(ToString(type));
        Sort(test_vec.begin(), test_vec.end(), comp, type);
    }
}

}// namespace sort