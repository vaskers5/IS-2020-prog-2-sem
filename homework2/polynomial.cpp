<<<<<<< HEAD:homework2/Polynomial.cpp
#include "polynomial.h"

using namespace std;

Polynomial::Polynomial() {
    max_pow = 0;
    min_pow = 0;
    size = max_pow + min_pow + 1;
    polynom = new int[size];
    for (int i = 0; i < size; i++) {
        polynom[i] = 0;
    }
}

Polynomial::Polynomial(int min, int max, const int *poly) {
    max_pow = max;
    min_pow = min;
    size = max_pow - min_pow + 1;
    polynom = new int[size];
    for (int i = 0; i < size; i++) {
        polynom[i] = poly[i];
    }
}
//fixed delete[]
Polynomial::~Polynomial() {
    delete[] polynom;
}

Polynomial::Polynomial(const Polynomial &another) {
    min_pow = another.min_pow;
    max_pow = another.max_pow;
    size = another.size;
    polynom = new int[size];
    for (int i = 0; i < size; i++) {
        polynom[i] = another.polynom[i];
    }
}

//fixed no default
Polynomial &Polynomial::operator=(const Polynomial &another) {
    min_pow = another.min_pow;
    max_pow = another.max_pow;
    size = another.size;
    polynom = new int[size];
    for (int i = 0; i < size; i++) {
        polynom[i] = another.polynom[i];
    }
    return *this;
}

int Polynomial::operator[](int number) const {
    if (number < min_pow || number > max_pow)
        return 0;
    return polynom[number - min_pow];
}

int &Polynomial::operator[](int number) {
    if (number < min_pow || number > max_pow)
        make(min(min_pow, number), max(max_pow, number));
    return polynom[number - min_pow];
}

void Polynomial::make(int new_min_pow, int new_max_pow) {
    int new_size = new_max_pow - new_min_pow + 1;
    int *kost = new int[new_size];
    for (int i = 0; i < new_size; i++) {
        kost[i] = 0;
    }
    Polynomial another(new_min_pow, new_max_pow, kost);
    for (int it = max(min_pow, new_min_pow); it <= min(max_pow, new_max_pow); it++) {
        another.polynom[it - new_min_pow] = polynom[it - min_pow];
    }
    *this = another;
}

bool Polynomial::operator==(const Polynomial &second) const {
    stringstream s1, s2;
    s1 << *this;
    s2 << second;
    return (s1.str() == s2.str());
}

bool Polynomial::operator!=(const Polynomial &second) const {
    return !(*this == second);
}

//fixed from +=
Polynomial Polynomial::operator+(const Polynomial &second) const {
    Polynomial another = Polynomial();
    another += *this;
    another += second;

    return another;

}

Polynomial &Polynomial::operator+=(const Polynomial &second) {
    int new_min_pow = min(min_pow, second.min_pow);
    int new_max_pow = max(max_pow, second.max_pow);
    int new_size;
    new_size = new_max_pow - new_min_pow + 1;

    int *kost = new int[new_size];

    for (int i = 0; i < new_max_pow - new_min_pow + 1; i++)
        kost[i] = 0;

    for (int i = 0; i < size; i++)
        kost[min_pow + i - new_min_pow] += polynom[i];

    for (int i = 0; i < second.size; i++)
        kost[second.min_pow + i - new_min_pow] += second.polynom[i];

    make(new_min_pow, new_max_pow);
    for (int i = 0; i < size; i++)
        this->polynom[i] = kost[i];
    this->min_pow = new_min_pow;
    this->max_pow = new_max_pow;
    this->size = size;
    return *this;
}

Polynomial Polynomial::operator-() const {
    int *temp = new int[size];
    for (int i = 0; i < size; i++)
        temp[i] = -polynom[i];

    return Polynomial(min_pow, max_pow, temp);
}

Polynomial Polynomial::operator-(const Polynomial &second) const {
    Polynomial check = *this + (-second);
    return check;
}

Polynomial & Polynomial::operator-=(const Polynomial &second) {
    *this = (*this - second);
    return *this;
}

Polynomial operator*(int number, Polynomial D) {
    for (int i = 0; i < D.size; i++)
        D.polynom[i] *= number;

    return D;
}

Polynomial Polynomial::operator*=(int number) {
    return *(this) * number;
}

Polynomial operator*(const Polynomial &first, const Polynomial &second) {
    int new_min = first.min_pow * second.min_pow;
    int new_max = first.max_pow * second.max_pow;
    int new_size = new_max - new_min + 1;
    int *comb_pol = new int[new_size];

    for (int i = 0; i < new_size; i++)
        comb_pol[i] = 0;
    for (int i = 0; i < first.size; i++)
        for (int j = 0; j < second.size; j++)
            comb_pol[first.min_pow + i + second.min_pow + j - new_min] += first.polynom[i] * second.polynom[j];
    return Polynomial(new_min, new_max, comb_pol);
}


//fixed for_each
Polynomial operator/(const Polynomial &another, int number) {
    Polynomial check = Polynomial(another);
    for_each(check.polynom, check.polynom+check.size, [&](int& poly){poly/=number;});
    return check;
}

//std::for_each(coefs, coefs+size, [&](int& coef){coef/=n;});
Polynomial Polynomial::operator/=(int number) const {
    return *this / number;
}

//fixed get O(n)
double Polynomial::get(int number) {
    double it = polynom[0] * powf(number, min_pow);
    double ans = it;
    for (int i = 1; i < size; i++) {
        it *= number;
        ans += polynom[i] * it;
    }
    return ans;
}

ostream &operator<<(ostream &output, const Polynomial &D) {
    if (D.size == 1) {
        output << D.polynom[0];
        return output;
    } else {
        int it = D.max_pow;
        int counter = 0;
        for (int i = D.size - 1; i >= 0; i--) {
            if (D.polynom[i] != 0) {
                if (counter > 0 and D.polynom[i] > 0)
                    output << "+";

                counter++;

                if (it != 1 and it != 0 and abs(D.polynom[i]) != 1)
                    output << D.polynom[i] << "x^" << it;

                if (it != 1 and it != 0 and D.polynom[i] == -1)
                    output << "-" << "x^" << it;

                if (it != 1 and it != 0 and D.polynom[i] == 1)
                    output << "x^" << it;

                if (it == 1 and abs(D.polynom[i]) != 1)
                    output << D.polynom[i] << "x";

                if (it == 1 and D.polynom[i] == 1)
                    output << "x";

                if (it == 1 and D.polynom[i] == -1)
                    output << "-x";
                if (it == 0)
                    output << D.polynom[i];
            }
            it--;
        }
        return output;
    }
=======
#include "polynomial.h"

using namespace std;

Polynomial::Polynomial() {
    max_pow = 0;
    min_pow = 0;
    size = max_pow + min_pow + 1;
    polynom = new int[size];
    for (int i = 0; i < size; i++) {
        polynom[i] = 0;
    }
}

Polynomial::Polynomial(int min, int max, const int *poly) {
    max_pow = max;
    min_pow = min;
    size = max_pow - min_pow + 1;
    polynom = new int[size];
    for (int i = 0; i < size; i++) {
        polynom[i] = poly[i];
    }
}
//fixed delete[]
Polynomial::~Polynomial() {
    delete[] polynom;
}

Polynomial::Polynomial(const Polynomial &another) {
    min_pow = another.min_pow;
    max_pow = another.max_pow;
    size = another.size;
    polynom = new int[size];
    for (int i = 0; i < size; i++) {
        polynom[i] = another.polynom[i];
    }
}

//fixed no default
Polynomial &Polynomial::operator=(const Polynomial &another) {
    min_pow = another.min_pow;
    max_pow = another.max_pow;
    size = another.size;
    polynom = new int[size];
    for (int i = 0; i < size; i++) {
        polynom[i] = another.polynom[i];
    }
    return *this;
}

int Polynomial::operator[](int number) const {
    if (number < min_pow || number > max_pow)
        return 0;
    return polynom[number - min_pow];
}

int &Polynomial::operator[](int number) {
    if (number < min_pow || number > max_pow)
        make(min(min_pow, number), max(max_pow, number));
    return polynom[number - min_pow];
}

void Polynomial::make(int new_min_pow, int new_max_pow) {
    int new_size = new_max_pow - new_min_pow + 1;
    int *kost = new int[new_size];
    for (int i = 0; i < new_size; i++) {
        kost[i] = 0;
    }
    Polynomial another(new_min_pow, new_max_pow, kost);
    for (int it = max(min_pow, new_min_pow); it <= min(max_pow, new_max_pow); it++) {
        another.polynom[it - new_min_pow] = polynom[it - min_pow];
    }
    *this = another;
}

bool Polynomial::operator==(const Polynomial &second) const {
    stringstream s1, s2;
    s1 << *this;
    s2 << second;
    return (s1.str() == s2.str());
}

bool Polynomial::operator!=(const Polynomial &second) const {
    return !(*this == second);
}

//fixed from +=
Polynomial Polynomial::operator+(const Polynomial &second) const {
    Polynomial another = Polynomial();
    another += *this;
    another += second;

    return another;

}

Polynomial &Polynomial::operator+=(const Polynomial &second) {
    int new_min_pow = min(min_pow, second.min_pow);
    int new_max_pow = max(max_pow, second.max_pow);
    int new_size;
    new_size = new_max_pow - new_min_pow + 1;

    int *kost = new int[new_size];

    for (int i = 0; i < new_max_pow - new_min_pow + 1; i++)
        kost[i] = 0;

    for (int i = 0; i < size; i++)
        kost[min_pow + i - new_min_pow] += polynom[i];

    for (int i = 0; i < second.size; i++)
        kost[second.min_pow + i - new_min_pow] += second.polynom[i];

    make(new_min_pow, new_max_pow);
    for (int i = 0; i < size; i++)
        this->polynom[i] = kost[i];
    this->min_pow = new_min_pow;
    this->max_pow = new_max_pow;
    this->size = size;
    return *this;
}

Polynomial Polynomial::operator-() const {
    int *temp = new int[size];
    for (int i = 0; i < size; i++)
        temp[i] = -polynom[i];

    return Polynomial(min_pow, max_pow, temp);
}

Polynomial Polynomial::operator-(const Polynomial &second) const {
    Polynomial check = *this + (-second);
    return check;
}

Polynomial & Polynomial::operator-=(const Polynomial &second) {
    *this = (*this - second);
    return *this;
}

Polynomial operator*(int number, Polynomial D) {
    for (int i = 0; i < D.size; i++)
        D.polynom[i] *= number;

    return D;
}

Polynomial Polynomial::operator*=(int number) {
    return *(this) * number;
}

Polynomial operator*(const Polynomial &first, const Polynomial &second) {
    int new_min = first.min_pow * second.min_pow;
    int new_max = first.max_pow * second.max_pow;
    int new_size = new_max - new_min + 1;
    int *comb_pol = new int[new_size];

    for (int i = 0; i < new_size; i++)
        comb_pol[i] = 0;
    for (int i = 0; i < first.size; i++)
        for (int j = 0; j < second.size; j++)
            comb_pol[first.min_pow + i + second.min_pow + j - new_min] += first.polynom[i] * second.polynom[j];
    return Polynomial(new_min, new_max, comb_pol);
}

Polynomial operator/(const Polynomial &another, int number) {
    int *kost = new int[another.size];
    //todo for_each
    for (int i = 0; i < another.size; i++)
        kost[i] = another.polynom[i] / number;

    return Polynomial(another.min_pow, another.max_pow, kost);
}

Polynomial Polynomial::operator/=(int number) const {
    return *this / number;
}

//fixed get O(n)
double Polynomial::get(int number) {
    double it = polynom[0] * powf(number, min_pow);
    double ans = it;
    for (int i = 1; i < size; i++) {
        it *= number;
        ans += polynom[i] * it;
    }
    return ans;
}

ostream &operator<<(ostream &output, const Polynomial &D) {
    if (D.size == 1) {
        output << D.polynom[0];
        return output;
    } else {
        int it = D.max_pow;
        int counter = 0;
        for (int i = D.size - 1; i >= 0; i--) {
            if (D.polynom[i] != 0) {
                if (counter > 0 and D.polynom[i] > 0)
                    output << "+";

                counter++;

                if (it != 1 and it != 0 and abs(D.polynom[i]) != 1)
                    output << D.polynom[i] << "x^" << it;

                if (it != 1 and it != 0 and D.polynom[i] == -1)
                    output << "-" << "x^" << it;

                if (it != 1 and it != 0 and D.polynom[i] == 1)
                    output << "x^" << it;

                if (it == 1 and abs(D.polynom[i]) != 1)
                    output << D.polynom[i] << "x";

                if (it == 1 and D.polynom[i] == 1)
                    output << "x";

                if (it == 1 and D.polynom[i] == -1)
                    output << "-x";
                if (it == 0)
                    output << D.polynom[i];
            }
            it--;
        }
        return output;
    }
>>>>>>> 77f42ef8aa0a3e9a6dd671a13f0bc3901f7c388c:homework2/polynomial.cpp
}