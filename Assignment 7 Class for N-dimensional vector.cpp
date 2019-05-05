// Assignment 7 

// Create a vector class for an n-dimentional vector



#include <iostream>
#include <cstdlib> // for exit()
#include <cmath>
#include <vector>
#include <initializer_list>  // for std::initializer_list


using namespace std;

// Vector Class for n-dimensional vector
class Vector
{
protected:
	double *m_data; // pointer to array that stores data of the vector
	int m_size; // size of vector (number of components in vector)
public:
	Vector() : m_data(nullptr), m_size(0) {} // default constructor
	Vector(int size, const initializer_list<double> &list); // parameterized constructor
	~Vector(); // destructor

	Vector(const Vector &x); // copy constructor
	Vector(Vector &&x); // move constructor
	Vector& operator=(const Vector &x); // copy assignment operator 
	Vector& operator=(Vector &&x); // move assignment operator

	double& operator[](int i); // accessor for ith component of vector where i>=1
	double operator[](int i) const;
	Vector operator*(double x);
	Vector operator+(Vector &x);

	friend ostream& operator<<(ostream &out, const Vector &x); // to output vector
	friend double dotProduct(const Vector &x, const Vector &y); // to calculate dot product

	double getSize();

};

// FourVector Class for Minowski four vector with format {ct,x,y,z}
class FourVector: public Vector
{
public:
	FourVector() : Vector() {}; // default constructor
	FourVector(double ct, double x, double y, double z); // parameterized constructor
	FourVector(double ct, Vector x); // parameterized constructor


	FourVector(const FourVector &x); // copy constructor
	FourVector(FourVector &&x); // move constructor
	FourVector& operator=(const FourVector &x); // copy assignment operator
	FourVector& operator=(FourVector &&x); // move assignment operator

	// Accessors
	double getCt() { return m_data[0]; }
	double getX() { return m_data[1]; }
	double getY() { return m_data[2]; }
	double getZ() { return m_data[3]; }

	friend ostream& operator<<(ostream &out, const FourVector &x); // to output FourVector
	friend double dotProduct(const FourVector &x, const FourVector &y); // to calculate dot product
	friend double LorentzBoost(const FourVector &x, const Vector &y); // to calculate Lorentz Boosted FourVector
};

// Particle Class
class Particle
{
private:
	FourVector m_pos;
	double m_mass;
	Vector m_beta;
public:
	// default constructor
	Particle() : m_pos(), m_mass(0), m_beta()
	{}
	// parameterized constructor
	Particle(FourVector pos, double mass, Vector beta) : m_pos(pos), m_mass(mass), m_beta(beta)
	{
		if (beta.getSize() != 3)
		{
			cout << "Error constructing Particle Class. Vector beta as argument is not size 3 vector. Exiting..." << endl;
			system("pause");
			exit(1);
		}
	}


	// function to calculate gamma
	double getGamma()
	{
		return 1 / sqrt(1 - dotProduct(m_beta, m_beta));
	}

	// function to calculate total energy in units of c^2
	double getTotEnerg()
	{
		return getGamma() * m_mass; 
	}

	// function to return momentum of particle in units of c 
	Vector getMomentum()
	{
		Vector result = m_beta * m_mass * getGamma();
		return result;
	}
};

// *--------------------------------------*
//   Member Functions for FourVector Class
// *--------------------------------------*

// Parameterized Constructor
FourVector::FourVector(double ct, double x, double y, double z) : Vector(4, { ct, x, y, z })
{}

// Parameterized Constructor
FourVector::FourVector(double ct, Vector x) : Vector(4, { ct, x[1], x[2], x[3] })
{
	if (x.getSize() != 3)
	{
		cout << "Error contruscting four vector. Vector argument is not size 3. Exiting..." << endl;
		system("pause");
		exit(1);
	}
}

// Copy Constructor
FourVector::FourVector(const FourVector &x) : Vector(4, { x[1], x[2], x[3], x[4] })
{}

// Move Constructor
FourVector::FourVector(FourVector &&x) : Vector()
{
	swap(m_size, x.m_size);
	swap(m_data, x.m_data);
}

// Copy Assignment Operator
FourVector& FourVector::operator=(const FourVector &x)
{
	if (this == &x)   // check for self-assignment
		return *this;

	delete[] m_data; // deallocate values and memory from m_data
	m_size = x.m_size; // shallow copy m_size

	m_data = new double[m_size]; // allocate memory for m_data
	for (int i = 0; i < m_size; i++) { m_data[i] = x.m_data[i]; } // do the copy

	return *this;
}

// Move Assignment Operator 
FourVector& FourVector::operator=(FourVector &&x)
{
	if (this == &x)  // check for self-assignment
		return *this;

	delete[] m_data; // deallocate values and memory from m_data

	// Swap values of *this and x
	swap(m_size, x.m_size);

	// Set Vector x to zero
	x.m_size = 0;
	x.m_data = nullptr;

	return *this;

}

// *--------------------------------------*
//   Friend Functions for FourVector Class
// *--------------------------------------*
ostream& operator<<(ostream &out, const FourVector &x)
{
	if (x.m_data) // if x.m_data not nullptr
	{
		out << "{";
		out << "ct:" << x[1] << " x:" << x[2] << " y:" << x[3] << " z:" << x[4];
		out << " }";
		return out;
	}

	else // if x.m_data is nullptr
	{
		out << 0;
		return out;
	}
}

double dotProduct(const FourVector &x, const FourVector &y)
{
	if (x.m_data == nullptr ||  y.m_data == nullptr)
	{
		return 0;
	}
	else
	{
		double result = x[1] * y[1] - x[2] * y[2] - x[3] * y[3] - x[4] * y[4];
		return result;
	}
}

FourVector LorentzBoost(FourVector &initial, Vector &beta) 
{
	if (beta.getSize() != 3) // if Vector beta not a 3 vector
	{
		cout << "Error. Cannot Lorentz Boost Fourvector with a vector argument that is not size 3. Exiting..." << endl;
		system("pause");
		exit(1);
	}
	else
	{
		FourVector result(0, 0, 0, 0);

		Vector x(3, { initial[2], 0, 0 });
		double gamma = 1 / sqrt(1 - dotProduct(beta, beta));
		double ct_i = initial[1];
		double ct_f = gamma * (ct_i - dotProduct(beta, x));

		Vector r_i(3, { initial[2], initial[3], initial[4] });
		Vector r_f = r_i + beta * ((gamma - 1) * dotProduct(r_i, beta) / dotProduct(beta, beta) - gamma*ct_i);

		result[1] = ct_f;
		result[2] = r_f[1]; result[3] = r_f[2]; result[4] = r_f[3];

		return result;
		 
	}
}





// *-----------------------------------*
//   Member Functions for Vector Class
// *-----------------------------------*

// Parameterized Constructor
// Arguments: Size of vector, 1D initializer list of matrix{ .. }
Vector::Vector(int size, const initializer_list<double> &list) : m_size(size)
{
	if (size != list.size()) // if arguments of constructor do not agree
	{
		cout << "Error initialising Vector class. Input of Vector size does not match size of input list for Vector. "
			<< "Exiting..." << endl;
		system("pause");
		exit(1); // exit program
	}

	m_data = new double[m_size]; // allocate memory for m_data

	// Initilize array from list
	int count = 0;
	for (double element : list)
	{
		m_data[count] = element;
		count++;
	}
}

// Destructor
Vector::~Vector()
{
	delete[] m_data;
}

// Copy Constructor 
Vector::Vector(const Vector &x) : m_size(x.m_size)
{
	if (x.m_data) // if x.m_data not null ptr
	{
		m_data = new double[m_size]; // allocate memory for m_data
		for (int i = 0; i < m_size; i++)  { m_data[i] = x.m_data[i]; } // do the copy
	}
	else // if x.m_data is null ptr
		m_data = nullptr;
}

// Copy Assignment Operator
Vector& Vector::operator=(const Vector &x)
{
	if (this == &x)   // check for self-assignment
		return *this;

	delete[] m_data; // deallocate values and memory from m_data
	m_size = x.m_size; // shallow copy m_size

	if (x.m_data)  // if x.m_data not null pointer, do deep copy
	{
		m_data = new double[m_size]; // allocate memory for m_data
		for (int i = 0; i < m_size; i++) { m_data[i] = x.m_data[i]; } // do the copy
	}

	else // if x.m_data is null pointer
		m_data = nullptr;

	return *this;
}

// Move Constructor 
Vector::Vector(Vector &&x)
{
	// shallow copy of x.m_size
	m_size = x.m_size;

	// shallow copy of x.m_data pointer
	m_data = x.m_data;

	// set Matrix x to zero
	x.m_size = 0;
	x.m_data = nullptr;
}

// Move Assignment Operator 
Vector& Vector::operator=(Vector &&x)
{
	if (this == &x)  // check for self-assignment
		return *this;

	delete[] m_data; // deallocate values and memory from m_data

	// Swap values of *this and x
	swap(m_size, x.m_size);

	// Set Vector x to zero
	x.m_size = 0;
	x.m_data = nullptr;

	return *this;

}

// Overloaded [] operator to access ith component of Vector. i >= 1.
double& Vector::operator[](int i) 
{
	if (i > m_size || i < 1) // if trying to access out of range
	{
		cout << "Error. Accessing vector component that is our of range. Exiting..";
		system("pause");
		exit(1); // exit program
	}

	else // if within range
		return m_data[i-1];
}

double Vector::operator[](int i) const
{
	if (i > m_size || i < 1) // if trying to access out of range
	{
		cout << "Error. Accessing vector component that is our of range. Exiting..";
		system("pause");
		exit(1); // exit program
	}

	else // if within range
		return m_data[i - 1];
}

double Vector::getSize()
{
	return m_size;
}

Vector Vector::operator*(double x)
{
	Vector result(3, { 0, 0, 0 });
	result[1] = m_data[0] * x;
	result[2] = m_data[1] * x;
	result[3] = m_data[2] * x;
	return result;
}

Vector Vector::operator+(Vector &x)
{
	Vector result(3, { 0, 0, 0 });
	result[1] = m_data[0] + x[1];
	result[2] = m_data[1] + x[2];
	result[3] = m_data[2] + x[3];
	return result;
}


// *-----------------------------------*
//   Friend Functions for Vector Class
// *-----------------------------------*
double dotProduct(const Vector &x, const Vector &y)
{
	if (x.m_size != y.m_size) // if vectors not of same size
	{
		cout << "Error. Cannot take dot product of vectors of different size. Exiting..." << endl;
		system("pause");
		exit(1); // exit program
	}

	else
	{
		double sum = 0;
		for (int i = 1; i <= x.m_size; i++)
		{
			sum += x[i] * y[i];
		}
		return sum;
	}
	
}

ostream& operator<<(ostream &out, const Vector &x)
{
	if (x.m_data) // if x.m_data not nullptr
	{
		out << "{"; 
		for (int i = 1; i <= x.m_size; i++)
		{
			out << " " << x[i];
		}
		out << " }";
		return out;
	}

	else // if x.m_data is nullptr
	{
		out << 0;
		return out;
	}
}






int main()
{
	// Demonstrate Vector Class
	Vector A; 
	Vector B(3, { 2, 2, 3 });
	Vector B_copy1(B);
	Vector B_copy2 = B;
	
	cout << "Demonstrate Vector Class: " << endl << endl;

	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	cout << "B_copy1: " << B_copy1 << " B_copy2: " << B_copy2 << endl ;
	cout << "3rd component of B is " << B[3] << endl;
	cout << "Dot product of B with itself: " << dotProduct(B, B) << endl << endl;

	Vector C(move(B_copy1));
	Vector D = move(B_copy2);
	cout << "After move, " << endl;
	cout << "C: " << C << " D: " << D << endl;
	cout << "B_copy1: " << B_copy1 << " B_copy2: " << B_copy2 << endl << endl;

	// Demonstrate FourVector Class
	FourVector F;
	FourVector G(1, 2, 3, 4);
	FourVector H(1, B);
	FourVector G_copy1(G);
	FourVector G_copy2 = G;

	cout << "Demonstrate FourVector Class:" << endl << endl;
	cout << "F: " << F << endl;
	cout << "G: " << G << endl;
	cout << "H: " << H << endl;
	cout << "G_copy1: " << G_copy1 << " G_copy2: " << G_copy2 << endl;
	cout << "ct component of G: " << G.getCt() << " x component of G: " << G.getX() << " y component of G: " << G.getY() << " z component of G: " << G.getZ();
	cout << "dot product of G with itself is: " << dotProduct(G, G) << endl;

	Vector I(move(G_copy1));
	Vector J = move(G_copy2);
	cout << "After move, " << endl;
	cout << "I: " << I << " J: " << J << endl;
	cout << "G_copy1: " << G_copy1 << " G_copy2: " << G_copy2 << endl << endl;

	FourVector K(1, 2, 3, 4);
	Vector L(3, { 0.1, 0.2, 0.3 });
	cout << "K: " << K << endl;
	cout << "L: " << L << endl;
	cout << "Lorentz Boost K with L gives" << LorentzBoost(K, L) << endl << endl;

	// Demonstrate Particle Class
	FourVector X(1, 2, 3, 4);
	Vector Y(3, { 0.1, 0.1, 0.1 });
	double Mass(10);
	Particle Z(X, Mass, Y);


	cout << "Demonstrate Particle Class:" << endl << endl;
	cout << "Particle Z has four vector for position " << K << ", mass " << Mass << " and 3 vector " << Y << endl;
	cout << "Total energy of Particle Z: " << Z.getTotEnerg() << "c^2." << endl;
	cout << "Momentum of Particle Z: " << Z.getMomentum() << "*c" << endl; 




	system("pause");
	return 0;
}