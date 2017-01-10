#pragma once

#include "gtest/gtest.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <typeinfo>

#define EXPECT_F_CALL(function) Mock::get().expectCall(function, __FILE__, __LINE__)

class Mock
{
    std::map<size_t*, std::string> expectedCalls_;
    Mock() {}
public:
    Mock(Mock&) = delete;
    Mock(Mock&&) = delete;
    Mock(const Mock&) = delete;
    Mock(const Mock&&) = delete;

    template <typename Type>
    void expectCall(Type address, const char* file, int line)
    {
        size_t* callAddress = reinterpret_cast<size_t*>(address);

        std::string name = file;
        name += ":";
        name += std::to_string(line);
        expectedCalls_[(callAddress)] = name;
    }

    template <typename Type>
    void call(Type address, const char* str)
    {
        size_t* callAddress = reinterpret_cast<size_t*>(address);
        auto result = expectedCalls_.find(callAddress);

        if (expectedCalls_.end() == result)
        {
            std::string error = "unexpected call of: ";
            error += str;
            throw std::range_error(error);
        }
        else
        {
            expectedCalls_.erase(result);
        }
    }

    void verify()
    {
        EXPECT_EQ(0, expectedCalls_.size());
        std::cerr << "Unresolved calls:" << std::endl;
        for (const auto& call : expectedCalls_)
        {
            std::cerr << call.second << std::endl;
        }
    }

    static Mock& get()
    {
        static Mock m;
        return m;
    }
};