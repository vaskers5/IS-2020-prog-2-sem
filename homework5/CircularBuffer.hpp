#ifndef HOMEWORK5_CIRCULARBUFFER_HPP
#define HOMEWORK5_CIRCULARBUFFER_HPP

#include <iostream>
#include <algorithm>
#include <iterator>


template<class T = unsigned>
class CircularBuffer {
//    T *m_first, *m_last, *m_cur_first, *m_cur_last;
    //todo capital letters are for consts
    int CAPACITY;
    int SIZE;
    int index_to_new_elem;
    T *data;
public:

    class Iter {
    private:
        T *iterator;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = value_type *;
        using reference = value_type &;

        Iter() : iterator(nullptr) {}

        explicit Iter(T *it) : iterator(it) {}

        Iter(const Iter &other) : iterator(other.iterator) {}

        Iter &operator+=(difference_type it) {
            iterator += it;
            return *this;
        }

        Iter &operator-=(difference_type it) {
            iterator -= it;
            return *this;
        }

        T &operator*() const {
            return *iterator;
        }

        T *operator->() const {
            return iterator;
        }


        Iter &operator++() {
            ++iterator;
            return *this;
        }

        Iter &operator--() {
            --iterator;
            return *this;
        }

        Iter operator++(T) const {
            Iter tmp(*this);
            ++iterator;
            return tmp;
        }

        Iter operator--(T) const {
            Iter tmp(*this);
            --iterator;
            return tmp;
        }

        difference_type operator-(const Iter &it) const {
            return iterator - it.iterator;
        }

        Iter operator+(difference_type it) const {
            return Iter(iterator + it);
        }

        Iter operator-(difference_type it) const {
            return Iter(iterator - it);
        }

        friend  Iter operator+(difference_type lhs, const Iter &rhs) {
            return Iter(lhs + rhs.iterator);
        }

        friend  Iter operator-(difference_type lhs, const Iter &rhs) {
            return Iter(lhs - rhs.iterator);
        }

        bool operator==(const Iter &other) const {
            return iterator == other.iterator;
        }

        bool operator!=(const Iter &other) const {
            return iterator != other.iterator;
        }

        bool operator>(const Iter &other) const {
            return iterator > other.iterator;
        }

        bool operator<(const Iter &other) const {
            return iterator < other.iterator;
        }

        bool operator>=(const Iter &other) const {
            return iterator >= other.iterator;
        }

        bool operator<=(const Iter &other) const {
            return iterator <= other.iterator;
        }
    };

    Iter begin() const {
        return Iter(data);
    }

    Iter end() const {
        return Iter(data + SIZE);
    }

    CircularBuffer(int CAPACITY = 1) : CAPACITY(CAPACITY), SIZE(0), index_to_new_elem(0), data(new T[CAPACITY]) {
        for (int i = 0; i < CAPACITY; ++i) {
            data[i] = 0;
        }
//        this->m_first = &data[0];
//        this->m_last = &data[CAPACITY - 1];
//        this->m_cur_first = &data[0];
//        this->m_cur_last= &data[CAPACITY - 1];
    }
    //todo delete buffer
    ~CircularBuffer() {}

    std::size_t size() {
        return SIZE;
    }
    //todo programming not physics
    const T &first() {
        if (SIZE == 0) {
            throw std::out_of_range("https://otvet.mail.ru/question/40252019");
        }
        return data[0];
    }

    const T &last() {
        if (SIZE == 0) {
            throw std::out_of_range("https://otvet.mail.ru/question/40252019");
        }
        return data[SIZE - 1];
    }

    //todo more information in exception
    T &operator[](int index) const {
//        if (index < 0 || index > SIZE - 1 || SIZE == 0) {
//            throw (std::out_of_range("out of range"));
//        }
        return data[index];
    }

    void changeCapacity(int newCapacity) {
        if (newCapacity <= CAPACITY) {
            throw std::bad_alloc();
        }
        T *data_ = new T[newCapacity];
        for (auto i = 0; i < SIZE; ++i) {
            data_[i] = data[i];
        }
        delete[] data;
        data = data_;
        CAPACITY = newCapacity;
        index_to_new_elem = SIZE;
    }
    //todo all functions O(1)
    void addLast(T x) {
        if (index_to_new_elem >= CAPACITY) {
            index_to_new_elem = 0;
        }
        if (SIZE == CAPACITY) {
            data[index_to_new_elem] = x;
        } else {
            T *data_ = new T[SIZE + 1];
            for (auto i = 0; i < SIZE; ++i) {
                data_[i] = data[i];
            }
            data_[SIZE] = x;
            delete[] data;
            data = data_;
            ++SIZE;
        }
        index_to_new_elem++;
    }

    void delLast() {
        if (SIZE == 0) {
            throw std::out_of_range("out of range");
        }
        T *data_ = new T[SIZE - 1];
        for (auto i = 0; i < SIZE - 1; ++i) {
            data_[i] = data[i];
        }
        delete[] data;
        data = data_;
        --SIZE;
    }

    void addFirst(T x) {
        if (SIZE == CAPACITY) {
            T *data_ = new T[SIZE];
            data_[0] = x;
            for (auto i = 1; i < SIZE; ++i) {
                data_[i] = data[i - 1];
            }
            delete[] data;
            data = data_;
        } else {
            T *data_ = new T[SIZE + 1];
            for (auto i = 1; i < SIZE + 1; ++i) {
                data_[i] = data[i - 1];
            }
            data_[0] = x;
            delete[] data;
            data = data_;
            ++SIZE;
        }
    }

    void delFirst() {
        if (SIZE == 0) {
            throw std::out_of_range("https://otvet.mail.ru/question/40252019");
        }
        T *data_ = new T[SIZE - 1];
        for (auto i = 0; i < SIZE; ++i) {
            data_[i] = data[i + 1];
        }
        delete[] data;
        data = data_;
        --SIZE;
    }

};

#endif //HOMEWORK5_CIRCULARBUFFER_HPP