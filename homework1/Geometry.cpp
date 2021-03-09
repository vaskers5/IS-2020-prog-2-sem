//fixed wtf
#include "Geometry.h"
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

Point::Point()
{
	coord_x = 0;
	coord_y = 0;
}

Point::Point(int x, int y) 
{
	coord_x = x;
	coord_y = y;
}

Point::Point(const Point& another_Point)
{
	coord_x = another_Point.coord_x;
	coord_y = another_Point.coord_y;
}

Point& Point::operator=(const Point& second)
{
	coord_x = second.coord_x;
	coord_y = second.coord_y;
	return *this;
}

void Point::setX(int x)
{
	coord_x = x;
}

int Point::getX() const
{
	return coord_x;
}

void Point::setY(int y)
{
	coord_y = y;
}

int Point::getY() const
{
	return coord_y;
}

PolygonalChain::PolygonalChain(int number, Point* a)
{
	poly_number = number;
	for (int i = 0; i < number; i++)
		poly_chain.push_back(a[i]);
}

PolygonalChain::PolygonalChain(const PolygonalChain& chain) { poly_number = chain.poly_number, poly_chain = chain.poly_chain; }

PolygonalChain& PolygonalChain::operator=(const PolygonalChain& second)
{
	poly_number = second.poly_number;
	poly_chain = second.poly_chain;
	return *this;
}

PolygonalChain:: ~PolygonalChain() {}

int PolygonalChain::getN() const
{
	return poly_number;
}

Point PolygonalChain::getPoint(int num) const
{
	return poly_chain[num];
}

double PolygonalChain::distance(Point first, Point second) const
{
	double distance = sqrt(pow(first.getX() - second.getX(), 2.0) + pow(first.getY() - second.getY(), 2.0));
	return distance;
}

int PolygonalChain::square_dist(Point first, Point second) const
{
	int dist = pow(first.getX() - second.getX(), 2.0) + pow(first.getY() - second.getY(), 2.0);
	return dist;
}

double PolygonalChain::perimeter()  const
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

ClosedPolygonalChain::ClosedPolygonalChain(int n, Point* a) : PolygonalChain(n, a) {}

ClosedPolygonalChain::ClosedPolygonalChain(const ClosedPolygonalChain& chain) : PolygonalChain(chain) {}

double ClosedPolygonalChain::perimeter()  const
{
	double per = PolygonalChain::perimeter();
	per += distance(getPoint(0), getPoint(getN() - 1));
	return per;
}

Polygon::Polygon(int n, Point* a) : ClosedPolygonalChain(n, a) {}

Polygon::Polygon(const Polygon& chain) : ClosedPolygonalChain(chain) {}

double Polygon::area() const
{
	int ar = 0.0;
	for (int i = 0; i < getN() - 1; i++)
	{
		int x = getPoint(i).getX();
		int y = getPoint(i + 1).getY();
		ar += x * y;
	}
	for (int i = 0; i < getN() - 1; i++)
	{
		int x = getPoint(i + 1).getX();
		int y = getPoint(i).getY();

		ar -= x * y;
	}
	return abs(ar) / 2;
}

Triangle::Triangle(int n, Point* a) : Polygon(n, a) {}

Triangle::Triangle(const Triangle& chain) : Polygon(chain) {}


bool Triangle::hasRightAngle() const
{
	int dist1 = square_dist(getPoint(0), getPoint(1));
	int dist2 = square_dist(getPoint(1), getPoint(2));
	int dist3 = square_dist(getPoint(0), getPoint(2));
	int sum_abc = dist1 + dist2 + dist3;
	int gip = max(dist1, max(dist2, dist3));
	return (sum_abc - gip == gip);
}

Trapezoid::Trapezoid(int n, Point* a) : Polygon(n, a) {}

Trapezoid::Trapezoid(const Trapezoid& chain) : Polygon(chain) {}


//do adecvat height
double Trapezoid::height() const
{
	double height = 0;
	double sum = 0.0;
	double first_base = distance(getPoint(1), getPoint(2));
	double second_base = distance(getPoint(3), getPoint(0));
	return 2 * (this->area()) / (first_base + second_base);
}

RegularPolygon::RegularPolygon(int n, Point* a) : Polygon(n, a) {}

RegularPolygon::RegularPolygon(const RegularPolygon& chain) : Polygon(chain) {}

double RegularPolygon::get_side()
{
	return distance(getPoint(0), getPoint(1));
}
double RegularPolygon::perimeter()
{
	return (this->get_side()) * (this->getN());
}

double RegularPolygon::area()
{
	double PI = 3.141592653589793238462643;
	return (pow((this->get_side()), 2.0) * getN()) / (4 * tan(PI / getN()));
}

