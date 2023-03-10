#include <iostream>
#include <string>
#include <functional>

#ifndef ASSERT_H
#define ASSERT_H

template<typename Predicate>
requires std::is_invocable_r_v<bool, Predicate>
void ASSERT(Predicate predicate, const std::string& message)
{
    if (!predicate()) {
        std::cout << message << std::endl;
        exit(1);
    }
}

template<typename A, typename B>
void ASSERT_EQUAL(const A& a, const B& b, const std::string& message)
{
    ASSERT(
        [&]() { return a == b; },
        message + " : expected values to be equal"
    );
}

template<typename T>
void ASSERT_NULL(const T* t, const std::string& message)
{
    ASSERT(
        [&]() { return t == nullptr; },
        message + " : expected value to be null"
    );
}

template<typename T>
void ASSERT_NOT_NULL(const T* t, const std::string& message)
{
    ASSERT(
        [&]() { return t != nullptr; },
        message + " : expected value to not be null"
    );
}

#endif
