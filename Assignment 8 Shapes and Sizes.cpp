// PHYS 30762 Object-Oriented C++
// Assignment 8
// Create classes for 2D and 3D shapes

#include "pch.h" // delete this when using school computer

#include <iostream>
#include <cstdlib> // for exit()
#include <cmath>
#include <string>
#include <math.h>
#include <vector>

using namespace std;
const double PI(3.14159265358979323);

//*==============================================
//   Abstract Base Class for general Shapes
//*==============================================

class Shape
{
protected:
	int m_dimen; // = 2 for 2D, = 3 for 3D
	string m_shape; 

	// make constructors protected because don't want people creating Shape objects directly
	Shape()  
		: m_dimen(0), m_shape("Undefined") {}
	Shape(int dimen)
		: m_dimen(dimen), m_shape("Undefined") {}
	Shape(int dimen, string shape)
		: m_dimen(dimen), m_shape(shape) {}

public:
	virtual ~Shape() {} 

	// Change value functions
	void setShape(string shape) { m_shape = shape; }
	void setDimen(int dimen) { m_dimen = dimen; }

	// Access functions
	int const getDimen() { return m_dimen; }
	string const getShape() { return m_shape; }

	virtual void report() = 0;
};

//*=============================================
//    Abstract Base Classes for 2D/3D Shapes
//*=============================================

class Shape2D : public Shape
{
protected:
	double m_width;
	double m_length;

	// make constructors protected because don't want people creating Shape2D objects directly
	Shape2D() : Shape(2) {}
	Shape2D(string shape) : Shape(2, shape) {}
	Shape2D(string shape, double width, double length) : Shape(2, shape), m_width(width), m_length(length) {}

public:
	virtual ~Shape2D() {}

	// Change value functions
	void setWidth(double width) { m_width = width; }
	void setLength(double length) { m_length = length; }

	// Access functions
	double const getWidth() { return m_width; }
	double const getLength() { return m_length; }

	// Area & Volume functions
	virtual double const getArea() = 0;
	double const getVolume() { return 0; }

	virtual void report() = 0;
};

class Shape3D : public Shape
{
protected:
	double m_width;
	double m_length;
	double m_height;

	// make constructors protected because don't want people creating Shape3D objects directly
	Shape3D() : Shape(3) {}
	Shape3D(string shape) : Shape(3, shape) {}
	Shape3D(string shape, double width, double length, double height) : Shape(3, shape), m_width(width), m_length(length), m_height(height) {}

public:
	virtual ~Shape3D() {}

	// Change value functions
	void setWidth(double width) { m_width = width; }
	void setLength(double length) { m_length = length; }
	void setHeight(double height) { m_height = height; }

	// Access functions
	double const getWidth() { return m_width; }
	double const getLength() { return m_length; }
	double const getHeight() { return m_height; }

	// Area & Volume functions
	virtual double const getArea() = 0; // surface area
	virtual double const getVolume() = 0;

	virtual void report() = 0;
};

//*============================
//     Derived 2D Objects
//*============================

class Square : public Shape2D
{
public:
	virtual ~Square() {}

	Square() : Shape2D("Square") {}
	Square(double length) : Shape2D("Square", length, length) {}

	virtual double const getArea() { return m_length * m_width; }

	virtual void report()
	{
		cout << "A square with sides of length " << m_width << ". Area: " << getArea() << ". Volume: " << getVolume() << ". ";
	}
};

class Rectangle : public Shape2D
{
public:
	virtual ~Rectangle() {}

	Rectangle() : Shape2D("Rectangle") {}
	Rectangle(double width, double length) : Shape2D("Rectangle", width, length) {}

	virtual double const getArea() { return m_length * m_width; }

	virtual void report()
	{
		cout << "A rectangle with width " << m_width << " and length " << m_length << ". Area: " << getArea() << ". Volume: " << getVolume() << ". ";
	}

};

class Ellipse : public Shape2D
{
public:
	virtual ~Ellipse() {}

	Ellipse() : Shape2D("Ellipse") {}
	Ellipse(double radius_a, double radius_b) : Shape2D("Ellipse", radius_a*2, radius_b*2) {}  

	virtual double const getArea() { return PI * (m_length/2) * (m_width/2); }

	virtual void report()
	{
		cout << "An ellipse with radius a " << m_width/2 << " and radius b " << m_length/2 << ". Area: " << getArea() << ". Volume: " << getVolume() << ". ";
	}


};

class Circle : public Shape2D
{
public:
	virtual ~Circle() {}

	Circle() : Shape2D("Circle") {}
	Circle(double radius) : Shape2D("Circle", radius*2, radius*2) {}

	virtual double const getArea() { return PI * (m_length / 2) * (m_width / 2); }

	virtual void report()
	{
		cout << "A circle with radius " << m_width/2 << ". Area: " << getArea() << ". Volume: " << getVolume() << ". ";
	}


};

//*=============================
//     Derived 3D Objects
//*=============================

class Cube : public Shape3D
{
public:
	virtual ~Cube() {}

	Cube() : Shape3D("Cube") {}
	Cube(double length) : Shape3D("Cube", length, length, length) {}

	virtual double const getArea() { return m_width * m_length * 6; }
	virtual double const getVolume() { return m_width * m_length * m_height; }

	virtual void report()
	{
		cout << "A cubes with sides " << m_width << ". Area: " << getArea() << ". Volume: " << getVolume() << ". ";
	}

};

class Cuboid : public Shape3D
{
public:
	virtual ~Cuboid() {}

	Cuboid() : Shape3D("Cuboid") {}
	Cuboid(double width, double length, double height) : Shape3D("Cuboid", width, length, height) {}

	virtual double const getArea() { return (m_width * m_length + m_length * m_height + m_height * m_width) * 2; }
	virtual double const getVolume() { return m_width * m_length * m_height; }

	virtual void report()
	{
		cout << "A cuboid with width " << m_width << ", length " << m_length << " and height " << m_height << ". Area: " << getArea() << ". Volume: " << getVolume() << ". ";
	}

};

class Sphere : public Shape3D
{
public:
	virtual ~Sphere() {}

	Sphere() : Shape3D("Sphere") {}
	Sphere(double radius) : Shape3D("Cube", radius*2, radius*2, radius*2) {}

	virtual double const getArea() { return 4 * PI * (m_width/2) * (m_width/2); }
	virtual double const getVolume() { return 4 * PI * (m_width/2) * (m_width/2) * (m_width/2) /3 ; }

	virtual void report()
	{
		cout << "A sphere with radius " << m_width/2 << ". Area: " << getArea() << ". Volume: " << getVolume() << ". ";
	}

};

class Ellipsoid : public Shape3D
{
public:
	virtual ~Ellipsoid() {}

	Ellipsoid() : Shape3D("Ellipsoid") {}
	Ellipsoid(double radius_a, double radius_b, double radius_c) : Shape3D("Cube", radius_a*2, radius_b*2, radius_c*2) {}

	virtual double const getArea() 
	{ 
		double a(m_width / 2); double b(m_length / 2); double c(m_height / 2);
		return 4 * PI * pow( ( pow(a*b, 1.6) + pow(a*c, 1.6) + pow(b*c, 1.6) ) / 3, 1 / 1.6);

	}
	virtual double const getVolume() { return 4 * PI * (m_width/2) * (m_length/2) * (m_height/2) / 3; }

	virtual void report()
	{
		cout << "An ellipsoid with radius a " << m_width/2 << ", radius b " << m_length/2 << " and radius c " << m_height/2 <<". Area: " << getArea() << ". Volume: " << getVolume() << ". ";
	}

};

class Prism : public Shape3D
{
private:
	double m_base_area; // pointer to 2D shape 
	string m_base_shape;
public:
	virtual ~Prism() {}

	Prism() : Shape3D("Prism") {}
	Prism(double height, Shape2D* base_shape) : Shape3D("Prism", base_shape->getWidth(), base_shape->getLength(), height), m_base_area(base_shape->getArea()), m_base_shape(base_shape->getShape()) {}

	virtual double const getVolume() { return m_height * m_base_area; }
	virtual double const getArea() 
	{ 
		cout << "Cannot calculate area for Prism" << endl;
		exit(1);
		return 0;
	}

	virtual void report()
	{
		cout << "A prism with base 2D shape " << m_base_shape << " of area " << m_base_area << " and depth " << m_height << ". Volume: " << getVolume() << ". ";
	}
};


 

//*===========================
//      Main Program
//*===========================

int main()
{
	vector<Shape*> vShapes;

	// Fill vShapes with shapes
	vShapes.push_back(new Square(5));
	vShapes.push_back(new Rectangle(2, 5));
	vShapes.push_back(new Circle(3));
	vShapes.push_back(new Ellipse(2, 4));
	vShapes.push_back(new Cube(6));
	vShapes.push_back(new Cuboid(3, 4, 5));
	vShapes.push_back(new Sphere(2));
	vShapes.push_back(new Ellipsoid(2, 3, 4));
	vShapes.push_back(new Prism(3, &Rectangle(2,3)));

	// Print information for shapes in vShapes
	for (int i = 0; i < vShapes.size(); i++)
	{
		vShapes[i]->report();
		cout << endl;
	}

	// Clear memory
	for (auto it = vShapes.begin(); it != vShapes.end(); ++it)
		delete *it;
	vShapes.clear();

	return 0;
}