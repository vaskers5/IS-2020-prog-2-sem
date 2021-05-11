#ifndef HOMEWORK4_PREDICATE_HPP
#define HOMEWORK4_PREDICATE_HPP

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template<typename T1, typename Function>
bool allOf(const T1 &begin, const T1 &end, Function func) {
    for (T1 it = begin;
         it != end; ++it) {
        if (!func(*it)) {
            return false;
        }
    }
    return true;
}


template<typename T1, typename Function>
bool anyOf(const T1 &begin, const T1 &end, Function func) {
    for (T1 it = begin; it != end; ++it) {
        if (func(*it)) {
            return true;
        }
    }
    return false;
}


template<typename T1, typename Function>
bool noneOf(const T1 &begin, const T1 &end, Function func) {
    for (T1 it = begin; it != end; ++it) {
        if (func(*it)) {
            return false;
        }
    }
    return true;
}

template<typename T1, typename Function>
bool oneOf(const T1 &begin, const T1 &end, Function func) {
    int count = 0;
    for (T1 it = begin; it != end; ++it) {
        if (func(*it)) {
            ++count;
        }
    }
    return count == 1;
}

template<typename T1, typename Function = std::less<>>
bool isSorted(const T1 &begin, const T1 &end, Function func = Function()) {
    for (T1 it = begin; it < end - 1; ++it) {
        if (!func(*it, *(it + 1))) {
            return false;
        }
    }
    return true;
}


template<typename T1, typename Function = std::less<>>
bool isPartitioned(T1 first, T1 last, Function func = Function()) {
    while (first != last) {
        if (!func(*first))
            break;
        ++first;
    }
    for (; first != last; ++first) {
        if (func(*first))
            return false;
    }
    return true;
}

template<typename T1, typename T2>
T1 findNot(const T1 &begin, const T1 &end, T2 elem) {
    for (T1 it = begin; it != end; ++it) {
        if (*it != elem) {
            return it;
        }
    }
    return end;
}

template<typename T1, typename T2>
T1 findBackward(const T1 &begin, const T1 &end, T2 elem) {
    stack<T1> q;
    for (T1 it = begin; it != end; it++)
        q.push(it);

    while (!q.empty()) {
        if (elem == *q.top())
            return q.top();
        q.pop();
    }
    return end;
}

template<typename T1, typename Function = std::less<>>
bool isPalindrome(const T1 &begin, const T1 &end, Function func = Function()) {
    vector<T1> data;
    for (T1 it = begin; it != end; it++)
        data.push_back(it);
    for (size_t i = 0; i < data.size() / 2; i++) {
        if (!func(*data[i], *data[data.size() - i - 1]))
            return false;
    }
    return true;
}

#endif //HOMEWORK4_PREDICATE_HPP
