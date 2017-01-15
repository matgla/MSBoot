#pragma once

#include <functional>
#include <iostream>

#include "stm32f4xx_gpio.h"
#include "stringify.hpp"

namespace comparators {

template <typename Type>
bool isEqual(const Type& a, const Type& b)
{
    if (a != b) {
        std::cerr << std::to_string(a) << " != " << std::to_string(b) << std::endl;
    }
    return a == b;
}

template <typename Type>
bool isEqual(const Type* a, const Type* b)
{
    if (a != b) {
        std::cerr << std::to_string(a) << " != " << std::to_string(b) << std::endl;
    }
    return a == b;
}

bool isEqual(GPIO_InitTypeDef* a, GPIO_InitTypeDef* b);

template <typename Tuple, std::size_t N>
struct TupleComparator {
    static bool isEqual(const Tuple& a, const Tuple& b)
    {
        return comparators::isEqual(std::get<N - 1>(a), std::get<N - 1>(b)) && TupleComparator<Tuple, N - 1>::isEqual(a, b);
    }
};

template <typename Tuple>
struct TupleComparator<Tuple, 1> {
    static bool isEqual(const Tuple& a, const Tuple& b)
    {
        return comparators::isEqual(std::get<0>(a), std::get<0>(b));
    }
};

template <typename... Args>
bool compareTuple(const std::tuple<Args...>& a, const std::tuple<Args...>& b)
{
    return TupleComparator<decltype(a), sizeof...(Args)>::isEqual(a, b);
}
}