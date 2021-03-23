#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

using  namespace std;

class Polynomial
{
private:
    int size, max_pow, min_pow;
    int* polynom;

public:

    Polynomial()
    {
        max_pow = 0;
        min_pow = 0;
        size = max_pow + min_pow + 1;
        polynom = new int[size];
        for (int i = 0; i < size; i++)
        {
            polynom[i] = 0;
        }
    }

    Polynomial(int min, int max, int* poly)
    {
        max_pow = max;
        min_pow = min;
        size = max_pow - min_pow + 1;
        polynom = new int[size];
        for (int i = 0; i < size; i++)
        {
            polynom[i] = poly[i];
        }
    }

    //fixed delete[]
    ~Polynomial()
    {
        delete[] polynom;
    }
    //fixed no default
    Polynomial(const Polynomial& another)
    {
        min_pow = another.min_pow;
        max_pow = another.max_pow;
        size = another.size;
        polynom = new int[size];
        for (int i = 0; i < size; i++)
        {
            polynom[i] = another.polynom[i];
        }
       // return *this;
    }

    //fixed no default
    Polynomial& operator=(const Polynomial& another)
    {
        min_pow = another.min_pow;
        max_pow = another.max_pow;
        size = another.size;
        for (int i = 0; i < size; i++)
        {
            polynom[i] = another.polynom[i];
        }
        return *this;
    }

    Polynomial (int min, int max)
    {
        max_pow = max;
        min_pow = min;
        size = max_pow - min_pow + 1;
        polynom = new int[size];
        for (int i = 0; i < size; i++)
        {
            polynom[i] = 0;
        }
    }
    int operator[](int p) const
    {
        if (p < min_pow || p > max_pow)
            return 0;
        return polynom[p - min_pow];
    }

    int& operator[](int p)
    {
        if (p < min_pow || p > max_pow)
            resize(std::min(min_pow, p), std::max(max_pow, p));
        return polynom[p - min_pow];
    }

    void resize(int newMinPow, int newMaxPow) {
        //fixed using
        Polynomial t(newMinPow, newMaxPow);
        for (int p = max(min_pow, newMinPow); p <= min(max_pow, newMaxPow); p++) {
            t.polynom[p - newMinPow] = polynom[p - min_pow];
        }

        *this = t;
    }

    bool operator==(const Polynomial& second) const
    {
        stringstream s1,s2;
        s1<<*this;
        s2<<second;
        return (s1.str()==s2.str());
    }

    bool operator!=(const Polynomial& second)
    {
        return !(*this == second);
    }

    //todo + from +=
    Polynomial operator+(const Polynomial& second) const
    {
        int new_min_pow = min(min_pow, second.min_pow);
        int new_max_pow = max(max_pow, second.max_pow);
        int new_size;
        new_size = new_max_pow - new_min_pow + 1;

        int* kost = new int[new_size];

        for (int i = 0; i < new_max_pow - new_min_pow + 1; i++)
            kost[i] = 0;

        for (int i = 0; i < size; i++)
            kost[min_pow + i - new_min_pow] += polynom[i];

        for (int i = 0; i < second.size; i++)
            kost[second.min_pow + i - new_min_pow] += second.polynom[i];

        return Polynomial(new_min_pow, new_max_pow, kost);

    }

    Polynomial& operator +=(const Polynomial& second)
    {
        *this = (*this + second);
        return *this;
    }

    Polynomial operator-() const
    {
        int *temp = new int[size];
        for (int i = 0; i < size; i++)
            temp[i] = -polynom[i];

        return Polynomial(min_pow, max_pow, temp);
    }

    Polynomial operator-(const Polynomial& second)
    {
        Polynomial check = *this + (-second);
        return check;
    }


    Polynomial& operator -=(const Polynomial& second)
    {
        *this = (*this - second);
        return *this;
    }

    Polynomial operator*(int number)
    {
        for (int i = 0; i < size; i++)
            polynom[i] *= number;

        return *this;
    }



    friend Polynomial operator/(const Polynomial& another, int number)
    {
        int* kost = new int[another.size];
        //todo for_each
        for (int i = 0; i < another.size; i++)
            kost[i] = another.polynom[i] / number;

        return Polynomial(another.min_pow,another.max_pow,kost);
    }

    Polynomial operator /=(int number)
    {
        return *this / number;
    }

    Polynomial operator *=(int number)
    {
        return *(this) * number;
    }
    //todo get O(n)
    double get(int number)
    {
        double it = polynom[0]*powf(number,min_pow);
        double ans = it;
        for (int i = 1; i < size; i++)
        {
            it*=number;
            ans += polynom[i]*it;
        }
        return ans;
    }

    friend ostream& operator<<(ostream& output, const Polynomial& D)
    {
        if (D.size == 1)
        {
            output << D.polynom[0];
            return output;
        }
        else
        {
            int it = D.max_pow;
            int counter = 0;
            for (int i = D.size - 1; i >= 0; i--)
            {
                if (D.polynom[i] != 0)
                {
                    if (counter > 0 and D.polynom[i] > 0)
                        output << "+";

                    counter++;

                    if (it != 1 and it != 0 and abs(D.polynom[i]) != 1)
                        output << D.polynom[i] << "x^" << it;

                    if (it != 1 and it != 0 and D.polynom[i] == -1)
                        output << "-" << "x^" << it;

                    if (it != 1 and it != 0 and D.polynom[i] == 1)
                        output << "x^" << it;

                    if (it == 1 and abs(D.polynom[i])!=1)
                        output << D.polynom[i] << "x";

                    if (it == 1 and D.polynom[i]==1)
                        output << "x";

                    if (it == 1 and D.polynom[i]==-1)
                        output << "-x";
                    if (it == 0)
                        output << D.polynom[i];
                }
                it--;
            }
            return output;
        }
    }
};

