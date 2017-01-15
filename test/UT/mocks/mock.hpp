#pragma once

#include "gtest/gtest.h"

#include <algorithm>
#include <exception>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "comparators.hpp"
#include "expectation.hpp"
#include "stringify.hpp"

#define _ANONYMOUS_BEGIN namespace mocks {
#define _ANONYMOUS_END }

#define _GEN_ARGS1(a1) \
    (a1 a)
#define _GEN_ARGS2(a1, a2) \
    (a1 a, a2 b)
#define _GEN_ARGS3(a1, a2, a3) \
    (a1 a, a2 b, a3 c)
#define _GEN_ARGS4(a1, a2, a3, a4) \
    (a1 a, a2 b, a3 c, a4 d)
#define _GEN_ARGS5(a1, a2, a3, a4, a5) \
    (a1 a, a2 b, a3 c, a4 d, a5 e)
#define _GEN_ARGS6(a1, a2, a3, a4, a5, a6) \
    (a1 a, a2 b, a3 c, a4 d, a5 e, a6 f)
#define _GEN_ARGS7(a1, a2, a3, a4, a5, a6, a7) \
    (a1 a, a2 b, a3 c, a4 d, a5 e, a6 f, a7 g)
#define _GEN_ARGS8(a1, a2, a3, a4, a5, a6, a7, a8) \
    (a1 a, a2 b, a3 c, a4 d, a5 e, a6 f, a7 g, a8 h)
#define _GEN_ARGS9(a1, a2, a3, a4, a5, a6, a7, a8, a9) \
    (a1 a, a2 b, a3 c, a4 d, a5 e, a6 f, a7 g, a8 h, a9 i)
#define _GEN_ARGS10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
    (a1 a, a2 b, a3 c, a4 d, a5 e, a6 f, a7 g, a8 h, a10 j)

#define _GET_VAL1(a1) \
    (a)
#define _GET_VAL2(a1, a2) \
    (a, b)
#define _GET_VAL3(a1, a2, a3) \
    (a, b, c)
#define _GET_VAL4(a1, a2, a3, a4) \
    (a, b, c, d)
#define _GET_VAL5(a1, a2, a3, a4, a5) \
    (a, b, c, d, e)
#define _GET_VAL6(a1, a2, a3, a4, a5, a6) \
    (a, b, c, d, e, f)
#define _GET_VAL7(a1, a2, a3, a4, a5, a6, a7) \
    (a, b, c, d, e, f, g)
#define _GET_VAL8(a1, a2, a3, a4, a5, a6, a7, a8) \
    (a, b, c, d, e, f, g, h)
#define _GET_VAL9(a1, a2, a3, a4, a5, a6, a7, a8, a9) \
    (a, b, c, d, e, f, g, h, i)
#define _GET_VAL10(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10) \
    (a, b, c, d, e, f, g, h, i, j)

#define DECLARE_MOCK_VOID_FUNCTION(function, ...)  \
    _ANONYMOUS_BEGIN                               \
    extern Mock<int, __VA_ARGS__> mock_##function; \
    _ANONYMOUS_END

#define DECLARE_MOCK_FUNCTION(returnType, function, ...)  \
    _ANONYMOUS_BEGIN                                      \
    extern Mock<returnType, __VA_ARGS__> mock_##function; \
    _ANONYMOUS_END

#define MOCK_VOID_FUNCTION(function, values, both, ...)         \
    _ANONYMOUS_BEGIN                                            \
    Mock<int, __VA_ARGS__> mock_##function((size_t*)&function); \
    _ANONYMOUS_END                                              \
    void function both                                          \
    {                                                           \
        auto& mock = GET_MOCK(function);                        \
        mock.call(std::make_tuple values, __FUNCTION__);        \
    }

#define MOCK_FUNCTION(returnType, function, values, both, ...)         \
    _ANONYMOUS_BEGIN                                                   \
    Mock<returnType, __VA_ARGS__> mock_##function((size_t*)&function); \
    _ANONYMOUS_END                                                     \
    void function both                                                 \
    {                                                                  \
        auto& mock = GET_MOCK(function);                               \
        mock.call(std::make_tuple values, __FUNCTION__);               \
        return mock.returnValue();                                     \
    }

#define DECLARE_NICEMOCK_VOID_FUNCTION(function, ...)      \
    _ANONYMOUS_BEGIN                                       \
    extern NiceMock<int, __VA_ARGS__> nicemock_##function; \
    _ANONYMOUS_END

#define DECLARE_NICEMOCK_FUNCTION(returnType, function, ...)      \
    _ANONYMOUS_BEGIN                                              \
    extern NiceMock<returnType, __VA_ARGS__> nicemock_##function; \
    _ANONYMOUS_END

#define NICEMOCK_VOID_FUNCTION(function, values, both, ...)             \
    _ANONYMOUS_BEGIN                                                    \
    NiceMock<int, __VA_ARGS__> nicemock_##function((size_t*)&function); \
    _ANONYMOUS_END                                                      \
    void function both                                                  \
    {                                                                   \
        auto& mock = GET_MOCK(function);                                \
        mock.call(std::make_tuple values, __FUNCTION__);                \
    }

#define NICEMOCK_FUNCTION(returnType, function, values, both, ...)         \
    _ANONYMOUS_BEGIN                                                       \
    NiceMock<returnType, __VA_ARGS__> mock_##function((size_t*)&function); \
    _ANONYMOUS_END                                                         \
    void function both                                                     \
    {                                                                      \
        auto& mock = GET_MOCK(function);                                   \
        mock.call(std::make_tuple values, __FUNCTION__);                   \
        return mock.returnValue();                                         \
    }

#define GET_MOCK(function) mocks::mock_##function

#define EXPECT_CALL(object, ...) \
    object.expectCall(std::make_tuple(__VA_ARGS__), __FILE__, __LINE__)

namespace mocks {
}

template <typename Tuple, std::size_t N>
struct TupleToString {
    static void toString(const Tuple& t, std::string& str)
    {
        TupleToString<Tuple, N - 1>::toString(t, str);
        str += ", ";
        str += std::to_string(std::get<N - 1>(t));
    }
};

template <typename Tuple>
struct TupleToString<Tuple, 1> {
    static void toString(const Tuple& t, std::string& str)
    {
        str += std::to_string(std::get<0>(t));
    }
};

template <typename... Args>
std::string tupleToString(const std::tuple<Args...>& t)
{
    std::string str = "(";
    TupleToString<decltype(t), sizeof...(Args)>::toString(t, str);
    str += ")";
    return str;
}

template <typename ReturnType, typename... Args>
class Mock {
protected:
    size_t* functionAddress_;
    std::vector<Expectation<Args...> > expectations_;
    int expected = 0;
    ReturnType returnValue_;

public:
    Mock() = delete;
    Mock(size_t* address)
        : functionAddress_(address)
    {
    }

    Mock(Mock&) = delete;
    Mock(Mock&&) = delete;
    Mock(const Mock&) = delete;
    Mock(const Mock&&) = delete;
    virtual ~Mock() = default;

    virtual void handleUnexpected(const std::tuple<Args...>& args, const char* name)
    {
        std::string error = "Unexpected call";
        error += ": ";
        error += name;
        error += tupleToString(args);

        std::cerr << "Unresolved calls:" << std::endl;
        for (const auto& call : expectations_) {
            std::cerr << call.getFile() << ":" << call.getLine() << std::endl;
        }

        throw std::range_error(error);
    }

    void call(const std::tuple<Args...>& args, const char* name)
    {
        if (0 == expectations_.size()) {
            handleUnexpected(args, name);
        }

        int position = -1;

        for (int i = 0; i < expectations_.size(); ++i) {
            auto& expectation = expectations_[i];
            if (comparators::compareTuple(expectation.getExpectedArgs(), args) && expectation.inSequence() && 0 == i) {
                position = 0;
                break;
            } else if (comparators::compareTuple(expectation.getExpectedArgs(), args) && !expectation.inSequence()) {
                position = i;
                break;
            }
        }

        if (position >= 0) {
            expectations_.erase(expectations_.begin() + position);
        } else {
            handleUnexpected(args, name);
            ;
        }
    }

    Expectation<Args...>& expectCall(std::tuple<Args...> args, const char* file,
        int line)
    {
        Expectation<Args...> expectation(args);
        expectation.setFile(file);
        expectation.setLine(line);
        expectations_.push_back(expectation);
        return expectations_[expectations_.size() - 1];
    }

    ReturnType returnValue() { return returnValue_; }

    void verify()
    {
        EXPECT_EQ(0, expectations_.size());
        std::cerr << "Unresolved calls:" << std::endl;
        for (const auto& call : expectations_) {
            std::cerr << call.getFile() << ":" << call.getLine() << std::endl;
        }
    }
};

template <typename ReturnType, typename... Args>
class NiceMock : public Mock<ReturnType, Args...> {
public:
    virtual void handleUnexpected(std::tuple<Args...>& args,
        const char* name) override
    {
    }
};