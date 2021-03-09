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
	Point();

	Point(int x, int y);

	Point(const Point& another_Point);

	Point& operator=(const Point& second);

	void setX(int x);

	int getX() const;

	void setY(int y);

	int getY() const;
};


class PolygonalChain
{
private:
	int poly_number;
	vector <Point> poly_chain;

public:
	PolygonalChain(int number, Point* a);

	PolygonalChain(const PolygonalChain& chain);

	PolygonalChain& operator=(const PolygonalChain& second);

	virtual ~PolygonalChain();

	int getN() const;

	Point getPoint(int num) const;

	double distance(Point first, Point second) const;

	int square_dist(Point first, Point second) const;

	virtual double perimeter()  const;

};

//fixed copy-paste


class ClosedPolygonalChain : public PolygonalChain
{
public:

	ClosedPolygonalChain(int n, Point* a);

	ClosedPolygonalChain(const ClosedPolygonalChain& chain);

	double perimeter()  const;
};

class Polygon : public ClosedPolygonalChain
{
public:
	Polygon(int n, Point* a);

	Polygon(const Polygon& chain);

	double area() const;
};

class Triangle : public Polygon
{
public:
	Triangle(int n, Point* a);

	Triangle(const Triangle& chain);
	//do without sqrt
	bool hasRightAngle() const;
};

class Trapezoid : public Polygon
{
public:
	Trapezoid(int n, Point* a);

	Trapezoid(const Trapezoid& chain);

	double height() const;

};
//fixed area and perimetr
class RegularPolygon : public Polygon
{
public:
	RegularPolygon(int n, Point* a);

	RegularPolygon(const RegularPolygon& chain);

	double get_side();

	double perimeter();

	double area();

};

