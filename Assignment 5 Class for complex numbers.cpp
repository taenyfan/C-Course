// PHYS 30762 Object-Oriented Programming in C++
// Assignment 5

// Create a class for complex numbers and overloading +, -, *, /, >>, << operators for complex numbers

#include <iostream>
#include <cmath>

using namespace std;

class Complex
{
private:
	double re; // real component
	double im;   // imaginary component

public:
	// Constructors & Destructor
	Complex()
	{
		re = 0; im = 0;
	}
	Complex(double real, double imag)
	{
		re = real; im = imag;
	}
	~Complex() {}

	// Functions to return real component and imaginary components 
	double getRe() const { return re; }
	double getIm() const { return im; }

	// Function to return modulus 
	double getMod() const { return sqrt(pow(re, 2) + pow(im, 2)); }

	// Function to return argument in radians between [-pi, +pi]
	double getArg() const { return atan2(im, re); }

	// Function to return complex conjugate
	Complex getConj() const { return Complex(re, -im); }

	// Functions to overload arithmetric operators + - * / 
	Complex operator+(const Complex &c) const;
	Complex operator-(const Complex &c) const;
	Complex operator*(const Complex &c) const; 
	Complex operator/(const Complex &c) const;

	// Friend function to overload << operator
	friend ostream& operator<<(ostream &out, const Complex &c);

	// Friend function to overload >> operator
	friend istream& operator>>(istream &in, Complex &c);

};

// Member function to overload + operator
Complex Complex::operator+(const Complex &c) const
{
	Complex result(re + c.re, im + c.im);
	return result;
}

// Member function to overload - operator
Complex Complex::operator-(const Complex &c) const
{
	Complex result(re - c.re, im - c.im);
	return result;
}

//Member function to overload * operator
Complex Complex::operator*(const Complex &c) const
{
	double newReal = re*c.re - im*c.im;
	double newImag = re*c.im + im*c.re;
	Complex result(newReal, newImag);
	return result; 
}

// Member function to overload / operator
Complex Complex::operator/(const Complex &c) const
{
	double denom = pow(c.re, 2) + pow(c.im, 2);
	double newReal = (re*c.re + im*c.im) / denom;
	double newImag = (im*c.re - re*c.im) / denom;
	Complex result(newReal, newImag);
	return result;
}

// Friend function of Class Complex to overload << operator
ostream& operator<<(ostream &out, const Complex &c)
{
	if (c.im == 0)        // cases: 1,4,-2
	{
		out << c.re;
		return out;
	}
	else if(c.re == 0)   // cases: 1i, -3i, 9i
	{
		out << c.im << "i";
		return out;
	}
	else if (c.im > 0) // cases: 1+9i, -2+9i
	{
		out << c.re << "+" << c.im << "i";
		return out;
	}
	else             // cases: 1-9i, -2-9i
	{
		cout << c.re << c.im << "i";
		return out;
	}
}

// Friend function of Class Complex to overload >> operator
// Able to read in a+ib or a-ib with BOTH a and b specified, even if 0
istream& operator>>(istream &in, Complex &c)
{
	char temp;  // to read in "+" or "-"
	in >> c.re; 
	in >> temp; 
	if (temp == 43) // if character is +
	{ 
		in >> c.im;  
	}
	else if (temp == 45) // if character is -
	{
		in >> c.im;
		c.im = -c.im;
	}
	return in;
}



int main()
{
	Complex A(3, +4);   // A = 3+4i
	Complex B(1,-2);    // B = 1-2i

	// Print A and B
	cout << "Defined A as " << A << " and B as " << B << endl << endl;

	// Print real, imaginary, modulus, argument, complex conjugate of A
	cout << "Real part of A is " << A.getRe() << endl;
	cout << "Imaginary part of A is " << A.getIm() << endl;
	cout << "Modulus of A is " << A.getMod() << endl;
	cout << "Argument of A is " << A.getArg() << endl; 
	cout << "Complex conjugate of A is " << A.getConj() << endl << endl;

	// Print A+B, A-B, A*B, A/B
	cout << "A+B = " << A + B << endl;
	cout << "A-B = " << A - B << endl;
	cout << "A*B = " << A*B << endl;
	cout << "A/B = " << A/B << endl << endl;

	// Ask user to enter a complex number and print it
	Complex complexInput;
	cout << "Enter a complex number:";
	cin >> complexInput;
	cout << "You entered: " << complexInput << endl;

	system("pause");
	return 0;
}