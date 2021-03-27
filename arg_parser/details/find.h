#pragma once

#include <algorithm>
#include <string>
#include <vector>

template <typename ValueType, class ContainerType>
auto find(const ContainerType &vec, const ValueType &val) {
    return std::find(vec.begin(), vec.end(), val);
}

template <class ContainerType, typename PredicateType>
auto find_if(const ContainerType &vec, PredicateType pred) {
    return std::find_if(std::begin(vec), std::end(vec), pred);
}

template <typename ValueType, class ContainerType>
bool have(const ContainerType &vec, const ValueType &val) {
    return find(vec, val) != vec.end();
}

template <typename PredicateType, class ContainerType>
bool have_if(const ContainerType &vec, const PredicateType &pred) {
    return find_if(vec, pred) != vec.end();
}