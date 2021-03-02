#pragma once
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Point
{
private:
	int coord_x, coord_y;

public:
	Point(int x = 0, int y = 0) : coord_x(x), coord_y(y) {}
	//todo second is a bad name
	Point(const Point& second)
	{
		coord_x = second.coord_x;
		coord_y = second.coord_y;
	}

	Point& operator=(const Point& second)
	{
		coord_x = second.coord_x;
		coord_y = second.coord_y;
		return *this;
	}

	void setX(int x)
	{
		coord_x = x;
	}
	int getX() const
	{
		return coord_x;
	}
	void setY(int y)
	{
		coord_y = y;
	}
	int getY() const
	{
		return coord_y;
	}
};

class Line
{
private:
	Point first, second;
	double k, b;
public:
	Line(Point p1, Point p2)
	{
		first = p1;
		second = p2;
		if (first.getX() != second.getX())
		{
			k = (first.getY() - second.getY()) / (first.getX() - second.getX());
			b = second.getY() - k * second.getX();
		}
		else
		{
			k = 0;
			b = 0;
		}

	}

	double getK() const
	{
		return k;
	}

	double getB() const
	{
		return b;
	}


	//TODO copy-paste
	double getDist() const
	{
		double distance = 0;
		distance = sqrt(pow(first.getX() - second.getX(), 2.0) + pow(first.getY() - second.getY(), 2.0));
		return distance;
	}
};

class PolygonalChain
{
private:
	int poly_number;
	vector <Point> poly_chain;

public:
	PolygonalChain(int number, Point* a)
	{
		poly_number = number;
		for (int i = 0; i < number; i++)
			poly_chain.push_back(a[i]);
	}

	PolygonalChain(const PolygonalChain& chain) : poly_number(chain.poly_number), poly_chain(chain.poly_chain) {}

	PolygonalChain& operator=(const PolygonalChain& second)
	{
		poly_number = second.poly_number;
		poly_chain = second.poly_chain;
		return *this;
	}

	virtual ~PolygonalChain()
	{
		//todo no clear in destructor, beeee
		poly_number = 0;
		poly_chain.clear();
	}

	int getN() const
	{
		return poly_number;
	}

	Point getPoint(int num) const
	{
		return poly_chain[num];
	}

	double distance(Point first, Point second) const
	{
		//todo = 0, why?
		double distance = 0;
		distance = sqrt(pow(first.getX() - second.getX(), 2.0) + pow(first.getY() - second.getY(), 2.0));
		return distance;
	}

	virtual double perimeter()  const
	{
		double per = 0;
		for (int i = 1; i < poly_number; i++)
		{
			Point first = poly_chain[i - 1];
			Point second = poly_chain[i];
			per += distance(first, second);
		}
		return per;
	}
};

class ClosedPolygonalChain : public PolygonalChain
{
public:

	ClosedPolygonalChain(int n, Point* a) : PolygonalChain(n, a) {}

	ClosedPolygonalChain(const ClosedPolygonalChain& chain) : PolygonalChain(chain) {}

	double perimeter()  const
	{
		double per = PolygonalChain::perimeter();
		per += distance(getPoint(0), getPoint(getN() - 1));
		return per;
	}
};

class Polygon : public ClosedPolygonalChain
{
public:
	Polygon(int n, Point* a) : ClosedPolygonalChain(n, a) {}

	Polygon(const Polygon& chain) : ClosedPolygonalChain(chain) {}

	double area() const
	{
		//todo doubles is overhead
		double ar = 0.0;
		for (int i = 0; i < getN() - 1; i++)
		{
			double x = getPoint(i).getX();
			double y = getPoint(i + 1).getY();
			ar += x * y;
		}
		for (int i = 0; i < getN() - 1; i++)
		{
			double x = getPoint(i + 1).getX();
			double y = getPoint(i).getY();

			ar -= x * y;
		}
		return abs(ar) / 2;
	}
};

class Triangle : public Polygon
{
public:
	Triangle(int n, Point* a) : Polygon(n, a) {}

	Triangle(const Triangle& chain) : Polygon(chain) {}


//todo without sqrt
	bool hasRightAngle() const
	{
		double dist1 = distance(getPoint(0), getPoint(1));
		double dist2 = distance(getPoint(1), getPoint(2));
		double dist3 = distance(getPoint(0), getPoint(2));
		double ar = 2 * area();
		if (dist1 * dist2 == ar or dist1 * dist3 == ar or dist2 * dist3 == ar)
			return true;
		else
			return false;
	}
};

class Trapezoid : public Polygon
{
public:
	Trapezoid(int n, Point* a) : Polygon(n, a) {}
	Trapezoid(const Trapezoid& chain) : Polygon(chain) {}



	double height() const
	{
		double height = 0;
		double sum = 0.0;
		vector <Line> lines = { Line(getPoint(0), getPoint(1)), Line(getPoint(1), getPoint(2)), Line(getPoint(2), getPoint(3)), Line(getPoint(3), getPoint(0)) };

		if (lines[0].getK() == lines[2].getK())
		{
			sum = lines[0].getDist() + lines[2].getDist();
			double height = 2 * area() / sum;
			return height;
		}
		if (lines[1].getK() == lines[3].getK())
		{
			sum = lines[1].getDist() + lines[3].getDist();
			double height = 2 * area() / sum;
			return height;
		}
		return height;
	}

};

//todo regular polygon area and perimeter
class RegularPolygon : public Polygon
{
public:

	RegularPolygon(int n, Point* a) : Polygon(n, a) {}

	RegularPolygon(const RegularPolygon& chain) : Polygon(chain) {}

};

