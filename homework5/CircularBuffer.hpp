#ifndef HOMEWORK5_CIRCULARBUFFER_HPP
#define HOMEWORK5_CIRCULARBUFFER_HPP

#include <iostream>
#include <algorithm>
#include <iterator>

template<class T>
class CircularBuffer {
private:
    int m_capacity = 0;
    int m_cur_size;
    T *data;
    T *m_end, *m_begin, *m_cur_first, *m_cur_last; // m_end и m_begin указывают на первый последний и неизменимы
public:
    // Итератор
    class iter : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        int index;
        size_t m_capacity, m_cur_size;
        T *m_begin, *m_end, *m_cur_first, *m_cur_last;
    public:

        iter(int index, size_t capacity, size_t cur_size, T *begin, T *end, T *cur_first, T *cur_last) :
                index(index), m_capacity(capacity), m_cur_size(cur_size), m_begin(begin), m_end(end),
                m_cur_first(cur_first), m_cur_last(cur_last) {}


        iter(const iter &it) : index(it.index), m_capacity(it.m_capacity), m_cur_size(it.m_cur_size),
                               m_begin(it.m_begin),
                               m_end(it.m_end), m_cur_first(it.m_cur_first), m_cur_last(it.m_cur_last) {}

//        iter &operator=(const iter &it) = default;

        // maybe to do, but i don't give a fuck
        iter &operator+=(int x) {
            index += x;

//            if (index > m_end)
//                index = m_begin + std::distance(m_end, index) - 1;

            return *this;
        }

        iter &operator-=(int x) {
            index -= x;

//            if (index < m_begin)
//                index = m_end - std::distance(index, m_begin) + 1;

            return *this;
        }

        iter &operator++() {
//            if (index < m_end)
                index++;
//            else {
//                index = m_begin;
//            }
            return *this;
        }

        iter &operator--() {
//            if (index > m_begin)
                index--;
//            else
//                index = m_end;
            return *this;
        }


        auto operator-(const iter &it) {
//            if (index < it.index) {
//                return std::distance(it.index, it.m_cur_last) +
//                       std::distance(m_cur_first, index + 1);
//            } else {
                return (index - it.index);
//            }
        }


        iter operator+(int x) {
            auto temp = index + x;
            

            return iter(index + x, m_capacity, m_cur_size, m_begin, m_end, m_cur_first, m_cur_last);
        }

        iter operator-(int x) {
            auto temp = index - x;

//            if (temp < m_begin)
//                temp = index + x + m_capacity - 1;

            return iter(temp, m_capacity, m_cur_size, m_begin, m_end, m_cur_first, m_cur_last);
        }

        T &operator*() const {

            if (m_cur_first + index > m_end)
                return *(m_cur_first + index - m_capacity);
            else
                return *(m_cur_first + index);
        }


        T *operator->() const {
            if (m_cur_first + index > m_end)
                return (m_cur_first + index - m_capacity);
            else
                return (m_cur_first + index);
        }

        T &operator[](const int x) {
            return *(*this + x);
        }

        bool operator==(const iter &x) const {
            return x.index == this->index;
        }

        bool operator!=(const iter &x) const {
            return x.index != this->index;
        }

        bool operator<(const iter &x) const {
            return x.index < this->index;
        }

        bool operator>(const iter &x) const {
            return x.index > this->index;
        }

        bool operator>=(const iter &x) const {
            return x.index >= this->index;
        }

        bool operator<=(const iter &x) const {
            return x.index <= this->index;
        }
    };


    CircularBuffer(int size_) {
        m_capacity = size_;
        data = new T[m_capacity + 1];
        m_end = &data[m_capacity - 1];
        m_begin = &data[0];
        m_cur_first = &data[m_capacity - 1];
        m_cur_last = &data[0];
        m_cur_size = 0;
    }

    CircularBuffer() {
        m_capacity = 0;
        data = new T[0];
        m_end = &data[0];
        m_begin = &data[0];
        m_cur_first = &data[0];
        m_cur_last = &data[0];
        m_cur_size = 0;
    }

    CircularBuffer(const CircularBuffer &buf) {
        m_capacity = buf.m_capacity;
        data = new T[m_capacity + 1];
        for (int i = 0; i < m_capacity; i++)
            data[i] = buf.data[i];

        m_end = &data[m_capacity - 1];
        m_begin = &data[0];
        m_cur_first = data + buf.m_cur_first - buf.data;
        m_cur_last = data + buf.m_cur_last - buf.data;
        m_cur_size = buf.m_cur_size;
    }

    CircularBuffer &operator=(const CircularBuffer &buf) {
        m_capacity = buf.m_capacity;
        data = new T[m_capacity + 1];
        for (int i = 0; i < m_capacity; i++)
            data[i] = buf.data[i];

        m_end = &data[m_capacity - 1];
        m_begin = &data[0];
        m_cur_first = data + (int) (buf.m_cur_first - buf.data);
        m_cur_last = data + (int) (buf.m_cur_last - buf.data);
        m_cur_size = buf.m_cur_size;

        return *this;
    }


    ~CircularBuffer() {
        delete[] data;
    }

    iter begin() const { // возвращает первый элемент
//        if (m_cur_last + 1 > m_end)
//            return iter(m_cur_first + 1, m_capacity, m_cur_size, m_begin, m_end + 1, m_cur_first, m_cur_last);
//        else
//            return iter(m_cur_first, m_capacity, m_cur_size, m_begin, m_end, m_cur_first, m_cur_last);
        return iter(0, m_capacity, m_cur_size, m_begin, m_end, m_cur_first, m_cur_last);
    }

    iter end() const {// возвращает последний элемент
//        if (m_cur_last + 1 > m_end)
//            return iter(m_cur_last + 1, m_capacity, m_cur_size, m_begin, m_end + 1, m_cur_first, m_cur_last);
//        else
//            return iter(m_cur_last, m_capacity, m_cur_size, m_begin, m_end, m_cur_first, m_cur_last);
        return iter(m_cur_size, m_capacity, m_cur_size, m_begin, m_end, m_cur_first, m_cur_last);
    }
    // 5 4 3 2
    // _ _ _ _ -> _ _ _ 1 -> _ _ 2 1 -> _ 3 2 1 -> 4 3 2 1 -> 4 3 2 5

    void addFirst(const T &value) {// вставка элемента в начало
        if (m_cur_size == 0) {
            *m_end = value;
            m_cur_last = m_end;
            m_cur_first = m_end;
        } else {
            cyclic_dec(m_cur_first);
            *m_cur_first = value;
        }

        if (m_cur_size < m_capacity) {
            m_cur_size++;
        } else {
//            data[m_capacity] = *m_cur_last;
            cyclic_dec(m_cur_last);

//              auto temp = m_cur_last;
//              *m_cur_last = data[m_capacity];
//              m_cur_last++;
        }
    }

// 4 3 2 1  -> _ 3 2 1 -> _ _ 2 1
    void delFirst() { // удаление элемента с начала
        if (m_cur_size == 0) {
            throw std::out_of_range("size is zero");
        }
        if (m_cur_size == 1) {
            m_cur_first = m_end;
            m_cur_last = m_begin;
        } else {
            if (m_cur_first + 1 > m_end)
                m_cur_first = m_begin;
            else
                m_cur_first++;
        }
        --m_cur_size;
    }

    const T &first() {
        if (m_cur_size == 0) {
            throw std::out_of_range("size is zero");
        }
        return *m_cur_first;
    }

    // _ _ _ _ -> 1 _ _ _ -> 1 2 _ _ -> 1 2 3 _ -> 1 2 3 4 -> 5 2 3 4
    void addLast(const T &value) { // вставка элемента в конец
        if (m_cur_last != m_end) {
            m_cur_last++;
            *m_cur_last = value;
        } else {
            m_cur_last = m_begin;
            *m_cur_last = value;
        }
        if (m_cur_size != m_capacity)
            m_cur_size++;
    }

    // _ _ _ _ -> 1 _ _ _ -> 1 2 _ _ -> 1 2 3 _ -> 1 2 3 4 -> 5 2 3 4
    // 1 2 3 4 - > 1 2 3
    // 5 2 3 4 - > 2 3 4
    void delLast() { // удаление элемента с конца
        if (m_cur_size == 0) {
            throw std::out_of_range("size is zero");
        }
        if (m_cur_size == 1) {
            m_cur_first = m_end;
            m_cur_last = m_begin;

        } else if (m_cur_last != m_begin) {
            m_cur_last--;

        }
        --m_cur_size;
    }

    const T &last() {
        if (m_cur_size == 0) {
            throw std::out_of_range("size is zero");
        }
        return *(m_cur_last);
    }

    T operator[](int i) const { // возвращает i-ый член
        if (m_cur_size != 0 and i < m_cur_size and i >= 0) {
            if (m_cur_first + i > m_end)
                return *(m_cur_first + i - m_capacity);
            else
                return *(m_cur_first + i);
        } else
            throw std::out_of_range("size is zero");
    }

    T &operator[](int i) { // возвращает i-ый член
        if (m_cur_size != 0 and i < m_cur_size and i >= 0) {
            if (m_cur_first + i > m_end)
                return *(m_cur_first + i - m_capacity);
            else
                return *(m_cur_first + i);
        } else
            throw std::out_of_range("size is zero");
    }

    void changeCapacity(const int &value) {
        CircularBuffer tmp(value);
        for (int i = m_cur_size - 1; i >= 0; --i) {
            tmp.addFirst((*this)[i]);
        }

        *this = tmp;
        /*
        T *temp = new T[value];
        int size = std::min(m_cur_size, value);
        for (int i = 0; i < size; ++i)
            temp[i] = *(m_cur_first - i);
        m_capacity = value;

//        delete[] data;
        data = new T[m_capacity];
        for (int i = 0; i < size; ++i)
            data[i] = temp[i];
        m_end = &data[m_capacity - 1];
        m_begin = data;
        m_cur_first = data + size;
        m_cur_last = m_begin;
        delete[] temp;
         */
    }

    void cyclic_inc(T *&ptr) {
        if (ptr == m_end) {
            ptr = m_begin;
        } else {
            ++ptr;
        }
    }

    void cyclic_dec(T *&ptr) {
        if (ptr == m_begin) {
            ptr = m_end;
        } else {
            --ptr;
        }
    }

};

#endif //HOMEWORK5_CIRCULARBUFFER_HPP
