#ifndef HOMEWORK4_PREDICATE_HPP
#define HOMEWORK4_PREDICATE_HPP

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//fixed bad names
template<typename Iterator, typename Function>
bool allOf(const Iterator &begin, const Iterator &end, Function func) {
    for (Iterator it = begin;
         it != end; ++it) {
        if (!func(*it)) {
            return false;
        }
    }
    return true;
}


template<typename Iterator, typename Function>
bool anyOf(const Iterator &begin, const Iterator &end, Function func) {
    for (Iterator it = begin; it != end; ++it) {
        if (func(*it)) {
            return true;
        }
    }
    return false;
}


template<typename Iterator, typename Function>
bool noneOf(const Iterator &begin, const Iterator &end, Function func) {
    for (Iterator it = begin; it != end; ++it) {
        if (func(*it)) {
            return false;
        }
    }
    return true;
}

template<typename Iterator, typename Function>
bool oneOf(const Iterator &begin, const Iterator &end, Function func) {
    int count = 0;
    for (Iterator it = begin; it != end; ++it) {
        if (func(*it)) {
            ++count;
        }
    }
    return count == 1;
}

template<typename Iterator, typename Function = std::less<>>
bool isSorted(const Iterator &begin, const Iterator &end, Function func = Function()) {
    for (Iterator it = begin; it < end - 1; ++it) {
        if (!func(*it, *(it + 1))) {
            return false;
        }
    }
    return true;
}


template<typename Iterator, typename Function = std::less<>>
bool isPartitioned(Iterator first, Iterator last, Function func = Function()) {
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

template<typename Iterator, typename Element>
Iterator findNot(const Iterator &begin, const Iterator &end, Element elem) {
    for (Iterator it = begin; it != end; ++it) {
        if (*it != elem) {
            return it;
        }
    }
    return end;
}

template<typename Iterator, typename Element>
Iterator findBackward(const Iterator &begin, const Iterator &end, Element elem) {
    stack<Iterator> q;
    for (Iterator it = begin; it != end; it++)
        q.push(it);

    while (!q.empty()) {
        if (elem == *q.top())
            return q.top();
        q.pop();
    }
    return end;
}

template<typename Iterator, typename Function = std::less<>>
bool isPalindrome(const Iterator &begin, const Iterator &end, Function func = Function()) {
    vector <Iterator> data;
    for (Iterator it = begin; it != end; it++)
        data.push_back(it);
    for (size_t i = 0; i < data.size() / 2; i++) {
        if (!func(*data[i], *data[data.size() - i - 1]))
            return false;
    }
    return true;
}

#endif //HOMEWORK4_PREDICATE_HPP
