#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>

using namespace std;

class Polynomial {
private:
    int size, max_pow, min_pow;
    int *polynom;

public:

    Polynomial();

    Polynomial(int min, int max, const int *poly);

    //fixed delete[]
    ~Polynomial();

    //fixed no default
    Polynomial(const Polynomial &another);

    //fixed no default
    Polynomial &operator=(const Polynomial &another);

    int operator[](int number) const;

    int &operator[](int number);

    void make(int new_min_pow, int new_max_pow);

    bool operator==(const Polynomial &second) const;

    bool operator!=(const Polynomial &second) const;

    //fixed from +=
    Polynomial operator+(const Polynomial &second) const;

    Polynomial &operator+=(const Polynomial &second);

    Polynomial operator-() const;

    Polynomial operator-(const Polynomial &second) const;


    Polynomial &operator-=(const Polynomial &second);

    friend Polynomial operator*(int number, Polynomial D);

    friend Polynomial operator*(const Polynomial &D, int number) {
        return number * D;
    }

    Polynomial operator*=(int number);

    friend Polynomial operator*(const Polynomial &first, const Polynomial &second);

    friend Polynomial operator/(const Polynomial &another, int number);

    Polynomial operator/=(int number) const;

    //fixed get O(n)
    double get(int number);

    friend ostream &operator<<(ostream &output, const Polynomial &D);
};