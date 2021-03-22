#pragma once
#include <iostream>
#include <vector>

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
	
	~Polynomial()
	{
		delete[] polynom;
	}

	Polynomial(const Polynomial& another)
	{
		size = another.size;
		min_pow = another.min_pow;
		max_pow = another.max_pow;
		polynom = new int[size];
		for (int i = 0; i < size; i++)
		{
			polynom[i] = another.polynom[i];
		}
	}


	Polynomial& operator=(const Polynomial& another) = default;


	int operator[](int p) const {
		if (p < min_pow || p > max_pow)
			return 0;
		return polynom[p - min_pow];
	}

	int& operator[](int p) {
		if (p < min_pow || p > max_pow)
		{	
			int new_size = max(max_pow, p) - min(min_pow, p) + 1;
			int* koef = new int[new_size];

			for (int i = 0; i < new_size; i++)
				koef[i] = 0;

			Polynomial check(min(min_pow, p), max(max_pow, p), koef);

			
			*this += check;
			cout << size<<"\n";
		}
			
		return polynom[p - min_pow];
	}

	bool operator==(const Polynomial& second) const
	{
		if (min_pow != second.min_pow)
			return false;
		for (int i = 0; i < size; i++)
		{
			if (second[i] != (*this)[i])
				return false;
		}
		return true;
	}

	bool operator!=(Polynomial& second)
	{
		return !(*this == second);
	}
	
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



	Polynomial operator-()
	{
		for (int i = 0; i < size; i++)
			polynom[i] = (-1)*polynom[i];

		return *this;
	}


	Polynomial operator-(Polynomial& second)
	{
		Polynomial check = *this + -second;
		return check;
	}

	Polynomial& operator +=(Polynomial& second)
	{
		*this =  (*this + second);
		return *this;
	}

	Polynomial& operator -=(Polynomial second)
	{
		*this = (*this - second);
		return *this;
	}

	Polynomial& operator*(int number)
	{
		for (int i = 0; i < size; i++)
			polynom[i] *= number;

		return *this;
	}

	friend Polynomial operator/(const Polynomial& another,int number)
	{
		int* kost = new int[another.size];
		for (int i = 0; i < another.size; i++)
			kost[i] = another.polynom[i]/number;

		return Polynomial(another.min_pow,another.max_pow,kost);
	}

	Polynomial operator /=(int number)
	{
		return *this / number;
	}

	Polynomial& operator *=(int number)
	{
		return *this * number;
	}

	double get(int number)
	{
		int it = min_pow;
		double ans = 0.0;
		for (int i = 0; i < size; i++)
		{
			ans += polynom[i]*pow(number, it);
			it++;
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
				if (D.polynom[i] != NULL)
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

					if (it == 1)
						output << D.polynom[i] << "x";

					if (it == 0)
						output << D.polynom[i];
				}
				it--;
			}
			return output;
		}
	}
};

