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
		max_pow = min;
		min_pow = max;
		size = max_pow + min_pow + 1;
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

	Polynomial(int min, int max)
	{
		min_pow = min;
		max_pow = max;
		size = min + max + 1;
		polynom = new int[size];
		for (int i = 0; i < size; i++)
			polynom[i] = 0;
	}

	Polynomial& operator=(const Polynomial& another) = default;
	/*{
		size = another.size;
		min_pow = another.min_pow;
		max_pow = another.max_pow;
		delete[] polynom;
		polynom = new int[size];
		for (int i = 0; i < size; i++)
		{
			polynom[i] = another.polynom[i];
		}
	}*/
	

	int operator[](int p) const 
	{
		if (p < min_pow || p > max_pow)
			return 0;
		return polynom[p - min_pow];
	}

	int& operator[](int p) 
	{
		if (p < min_pow || p > max_pow)
			resize(min(min_pow, p), max(max_pow, p));
		return polynom[p - min_pow];
	}

	void resize(int newMinPow, int newMaxPow)
	{
		//fixed using
		Polynomial t(newMinPow, newMaxPow);
		for (int p = max(min_pow, newMinPow); p <= min(max_pow, newMaxPow); p++) 
		{
			t.polynom[p - newMinPow] = polynom[p - min_pow];
		}

		*this = t;
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
		int* kost = new int[second.size];
		for (int i = 0; i < second.size; i++)
			kost[i] = polynom[i] + second.polynom[i];
			
		//delete[] kost;
		return 	Polynomial(second.min_pow, second.max_pow, kost);
	}

	Polynomial operator-()
	{
		for (int i = 0; i < size; i++)
			polynom[i] = -polynom[i];

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

	/*Polynomial& operator*(Polynomial& second)
	{
		int new_max = max_pow * second.max_pow;

	} */

	Polynomial& operator/(int number)
	{
		for (int i = 0; i < size; i++)
			polynom[i] /= number;
		return *this;
	}

	Polynomial& operator *=(int number)
	{
		return *this * number;
	}

	Polynomial& operator /=(int number)
	{
		return *this / number;
	}

	friend ostream& operator<<(ostream& output, const Polynomial& D) 
	{
		int it = D.max_pow;
		for (int i = D.size-1; i >0; i++)
		{
			if (D.polynom[i]!=NULL)
				output << D.polynom[i] << "x^" << D.max_pow - i<<" ";
		}
		return output;
	}
};

