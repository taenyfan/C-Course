// PHYS 30762 Programming in C++
// Assignment 6

// Create a class for a Matrix 
// e.g. for a matrix [ 4 5 6  ]
//                   [ 5 3 2  ]

#include <iostream>
#include <cstdlib> // for exit()
#include <cmath>
#include <vector>
#include <initializer_list>  // for std::initializer_list


using namespace std;

class Matrix
{
private:
	double *m_data; // pointer to matrix array
	int m_rows;
	int m_columns; 
	int m_totalSize;
public:
	//=============================== Constructors & Destructor =================================

	// Default Constructor
	Matrix() : m_data(nullptr), m_rows(0), m_columns(0), m_totalSize(0) 
	{}

	// Parameterized Zero Matrix Constructor
	// Arguments: No. of rows in matrix, no. of columns in matrix
	// Creates: 1D zero matrix of M rows, N columns
	Matrix(int rows, int columns) : m_rows(rows), m_columns(columns)
	{
		m_totalSize = m_rows * m_columns;
		m_data = new double[m_totalSize];      // create dynamic array m_data to store matrix data

		for (int i = 0; i < m_totalSize; i++)  // assign 0 to all elements in m_data array
		{
			m_data[i] = 0;					 
		}
	}

	// Parameterized Matrix Constructor via list initialization
	// Arguments: No. of rows in matrix, no. of columns in matrix, 1D initializer list of matrix {..}
	// Creates: 1D matrix of M rows, N columns IF initializer list input satisfies rows, columns requirements, else exit
	Matrix(int rows, int columns, const initializer_list<double> &list) : m_rows(rows), m_columns(columns)
	{
		m_totalSize = m_rows * m_columns; 

		if (m_totalSize != list.size()) // if no. of rows and columns do not match initializer list
		{
			cout << "Error with initiliazing Matrix class via list initialization. No. of rows and no. columns "
				<< "do not match no. of elements in intilizer list. Exiting..." << endl;
			system("pause"); 
			exit(1); // exit program

		}

		else  // if no. of rows and columns match inializer list
		{
			m_data = new double[m_totalSize];	// create dynamic array m_data to store matrix data

			// Initilize array from list
			int count = 0;
			for (double element : list)
			{
				m_data[count] = element;
				count++;
			}

		}

	}

	// Parameterized Matrix Constructor via vecotr<double> list initialization
	// Arguments: No. of rows in matrix, no. of columns in matrix, 1D vector<double> list of matrix {..}
	// Creates: 1D matrix of M rows, N columns IF initializer list input satisfies rows, columns requirements, else exit
	Matrix(int rows, int columns, const vector<double> &list) : m_rows(rows), m_columns(columns)
	{
		m_totalSize = m_rows * m_columns;

		if (m_totalSize != list.size()) // if no. of rows and columns do not match initializer list
		{
			cout << "Error with initiliazing Matrix class via list initialization. No. of rows and no. columns "
				<< "do not match no. of elements in intilizer list. Exiting..." << endl;
			system("pause");
			exit(1); // exit program

		}

		else  // if no. of rows and columns match inializer list
		{
			m_data = new double[m_totalSize];	// create dynamic array m_data to store matrix data

			// Initilize array from list
			int count = 0;
			for (double element : list)
			{
				m_data[count] = element;
				count++;
			}

		}

	}



	// Copy Constructor via Deep Copy
	Matrix(const Matrix &x) : m_rows(x.m_rows), m_columns(x.m_columns), m_totalSize(x.m_totalSize)
	{
		if (x.m_data) // if x.m_data is not null pointer, do deep copy
		{
			m_data = new double[m_totalSize];  // allocate memory for m_data
			for (int i = 0; i < m_totalSize; i++)  { m_data[i] = x.m_data[i]; } // do the copy
		}

		else   // if x.m_data is null pointer
			m_data = nullptr;
	}

	// Move Constructor via stealing data
	Matrix(Matrix &&x)
	{
		// shallow copy of m_rows, m_columns, m_totalSize
		m_rows = x.m_rows;
		m_columns = x.m_columns;
		m_totalSize = x.m_totalSize;

		// shallow copy of x.m_data pointer
		m_data = x.m_data;  

		// set Matrix x to zero
		x.m_rows = x.m_columns = x.m_totalSize = 0;
		x.m_data = nullptr;
	}

	// Destructor 
	~Matrix()
	{
		delete[] m_data;
	}

	//============================= Overloaded Assignment Operators =====================================

	// Copy Assignment Operator via Deep Copy
	Matrix& operator=(const Matrix &x)
	{
		if (this == &x)   // check for self-assignment
			return *this;

		delete[] m_data; // deallocate values and memory from m_data
		m_rows = x.m_rows; m_columns = x.m_columns; m_totalSize = x.m_totalSize; // shallow copy rows, columns, totalSize

		if (x.m_data)  // if x.m_data not null pointer, do deep copy
		{
			m_data = new double[m_totalSize]; // allocate memory for m_data
			for (int i = 0; i < m_totalSize; i++) { m_data[i] = x.m_data[i]; } // do the copy
		}

		else // if x.m_data is null pointer
			m_data = nullptr;

		return *this;
	}

	// Move Assignment Operator via stealing data
	Matrix& operator=(Matrix &&x)
	{
		if (this == &x)  // check for self-assignment
			return *this;

		delete[] m_data; // deallocate values and memory from m_data

		// Swap values of *this and x
		swap(m_rows, x.m_rows);
		swap(m_columns, x.m_columns);
		swap(m_totalSize, x.m_totalSize);
		swap(m_data, x.m_data);

		// Set Matrix x to zero
		x.m_rows = x.m_columns = x.m_totalSize = 0;
		x.m_data = nullptr;

		return *this;

	}

	//============================== Access Functions =======================================

	// Function to return No. of Rows
	int getRows() const { return m_rows; }

	// Function to return No. of Columns
	int getColumns() const { return m_columns; }

	// Function to return No. of Elements in Matrix
	int getSize() const { return m_totalSize; }

	// Function to return position of matrix element A_ij in 1D m_data array
	int getPos(int i, int j) const
	{
		if ( i>0 && j>0 && i<= m_rows && j<=m_columns )  // if i and j positive and within range
		{
			return (j - 1) + (i - 1)*m_columns;
		}

		else // if i and j negative or out of range
		{
			cout << "Error getting position of matrix element in 1D array. Exiting..." << endl;
			system("pause");
			exit(1); // exit program
		}
	}

	// Function to return matrix element A_ij from 1D m_data array
	double getElem(int i, int j) const
	{
		return m_data[getPos(i, j)];
	}

	// Overload () operator to return matrix element A_ij from 1D m_data array
	// i.e x(1,2) returns x_12 element from Matrix x
	double& operator()(int i, int j)
	{
		return m_data[getPos(i, j)];
	}

	// ========== Member function to return matrix with row m and column n deleted ===============
	Matrix getDel(int m, int n) const
	{

		vector<double> list; // list to append values of matrix element after deleting row m and row n

		for (int i = 1; i <= m_rows; i++)
		{
			if (i == m) continue; // do not append values into list from row m 
			for (int j = 1; j <= m_columns; j++)
			{
				if (j == n) continue; // do not append values into list from column n
				list.push_back((*this).getElem(i, j)); // append valid values from m_data into list
			}
		}

		Matrix result(m_rows - 1, m_columns - 1, list); // initialise result matrix

		return result;

	}

	// ============== Member function to return determinant of square matrix ==================
	double getDet() 
	{
		Matrix temp(*this); 

		
		// If not a square matrix
		if (m_rows != m_columns)
		{
			cout << "Not a square matrix. Cannot calcaulate determinant. Exiting..." << endl;
			system("pause");
			exit(1); // exit program
		}

		else
		{
			if (m_rows == 1 && m_columns == 1) return temp(1, 1); // if matrix has 1 element
			if (m_rows == 0 && m_columns == 0) return 0;  // if zero matrix
 			// If matrix is 2 x 2 dimensions
			if (m_rows == 2 && m_columns == 2) 
			{
				return temp(1, 1)*temp(2, 2) - temp(1, 2)*temp(2, 1);
			}

			else{  // by recursion
				double det = 0;
				for (int i = 1; i <= m_columns; i++)
				{
					Matrix temp2 = temp.getDel(1, i);
					det += pow(-1, i + 1) * temp(1, i) * temp2.getDet();
				}
				return det;
			}
		}
	}

	//======================== Overloaded Input & Output Operators===========================

	friend ostream& operator<<(ostream &out, const Matrix &rhs);
	friend istream& operator>>(istream &in,  Matrix &rhs);

	//===================== Overloaded Arithmetric Operators =============================
	Matrix operator+(const Matrix &x) 
	{
		// If dimensions of both Matrix match
		if (m_rows == x.m_rows && m_columns == x.m_columns && m_totalSize == x.m_totalSize)
		{
			Matrix result(m_rows, m_columns); // create zero matrix of same dimension

			for (int i = 0; i < m_totalSize; i++)
			{
				result.m_data[i] = m_data[i] + x.m_data[i];
			}

			return result;
		}

		// If dimensions of both Matrix do not match, exit
		else
		{
			cout << "Addition of matrices failed. Dimensions of matrices do not match. Exiting...";
			system("pause");
			exit(1); // exit program
		}
	}

	Matrix operator-(const Matrix &x) 
	{
		// If dimensions of both Matrix match
		if (m_rows == x.m_rows && m_columns == x.m_columns && m_totalSize == x.m_totalSize)
		{
			Matrix result(m_rows, m_columns); // create zero matrix of same dimension

			for (int i = 0; i < m_totalSize; i++)
			{
				result.m_data[i] = m_data[i] - x.m_data[i];
			}

			return result;
		}

		// If dimensions of both Matrix do noe match, exit
		else
		{
			cout << "Subtraction of matrices failed. Dimensions of matrices do not match. Exiting...";
			system("pause");
			exit(1); // exit program
		}
	}

	Matrix operator*(const Matrix &x)
	{
		// If m_columnns match x.m_rows, multiplication possible
		if (m_columns == x.m_rows)
		{
			Matrix result(m_rows, x.m_columns); // create zero matrix of appropriate dimentsion
			
			for (int i = 1; i <= result.m_rows; i++) 
			{
				for (int j = 1; j <= result.m_columns; j++)
				{
					double sum = 0; 
					for (int k = 1; k <= m_columns; k++)
					{
						sum = sum + (*this).getElem(i, k) * x.getElem(k, j);
					}
					result.m_data[result.getPos(i, j)] = sum;
				}
			}

			return result;
		}
		else
		{
			cout << "Multiplication failed. Dimensions of matrices not appropriate. Exiting..." << endl;
			system("pause");
			exit(1);
		}
	}


}; // end of class Matrix

//=========================== Friend Functions =================================

// Prints out matrix on the next line, with each row on a new line
ostream& operator<<(ostream &out, const Matrix &x)
{
	out << endl;  // print matrix on next line

	if (x.m_data)  // if x.m_data is not null pointer, print out the values in x.m_data
	{
		for (int i = 1; i <= x.m_rows; i++)
		{
			for (int j = 1; j <= x.m_columns; j++) { out << x.getElem(i, j) << " "; }  // elements in the same row are put on the same line
			out << endl; // begin a new line for elements in the next row
		}
		return out;
	}

	else
	{
		out << 0 << endl;
		return out;
	}
}

// Reads in matrix if given input in the form: "rows columns A_11 A_12 A_21 A_22" where rows and columns are integers
// e.g. 2 2 1 1 2 2  1st number indicates no. of rows, 2nd number indicates no. of columns 
// and the rest are the matrix elements A_11, A_12, A_21, A_22
istream& operator>>(istream &in,  Matrix &x)
{
	in >> x.m_rows;  
	in >> x.m_columns; 

	if (x.m_rows == 0 || x.m_columns == 0) { x = Matrix(); return in; } // if user entered zero matrix

	x.m_totalSize = x.m_rows * x.m_columns; 

	delete[] x.m_data; // deallocate values and memory from x.m_data
	x.m_data = new double[x.m_totalSize]; // allocate memory for x.m_data

	// Read the rest of the input into x.m_data
	int i = 0;
	while (in >> x.m_data[i])
	{
		i++;
	}

	// Exit if size of Matrix x does not match the number of matrix elements inputted by user. 
	if (x.m_totalSize != i)
	{
		cout << "Inputs of matrix elements do not agree with size of matrix. Exiting..." << endl;
		system("pause");
		exit(1);
	}

	return in;
}



int main()
{
	const Matrix E(2, 2, { 1, 2, 3, 4 }); // const Matrix to demonstrate how to input a matrix

	// Demonstrate parameterized constructors, deep copy constructors and deep copy assignment 
	Matrix A; // null matrix by Default Constructor
	Matrix B(2, 3); // 2 x 3 zero matrix by Parameterized Zero Matrix Constructor 
	Matrix C(2, 3, { 1, 1, 1, 2, 2, 2 }); // 2 x 3 non-zero matrix by Parameterized Matrix Constructor via list initialization
	Matrix D(C); // 2 x 3 non-zero matrix by Copy Constructor via Deep Copy


	cout << "Matrix A by default null matrix constructor: " << A;
	cout << "Matrix B by parameterized zero matrix constuctor : " << B;
	cout << "Matrix C by parameterized constructor: " << C;
	cout << "Matrix D by Deep Copy from Matrix C: " << D;

	cout << "Change values of Matrix C to that of Matrix B:" ;
	C = B;
	cout << C;
	cout << "Matrix D values remain unchanged: " << D ;

	// Demonstrate move constructor 
	cout << endl << "Demonstrate move constructor" << endl;

	Matrix m1(2, 2, { 1, 1, 2, 2 });
	cout << "Matrix m1: " << m1;

	Matrix m2( move(m1) ); // construct m2 by move constructor
	cout << "Matrix m2 by move constructor using m1: " << m2;

	cout << "Matrix m1 after being moved: " << m1;

	// Demonstrate move assignment
	cout << endl << "Demonstrate move assignment" << endl; 

	Matrix a1; // null matrix
	Matrix a2(2, 3, { 1, 2, 3, 4, 5, 6 });
	cout << "Matrix a1: " << a1;
	cout << "Matrix a2: " << a2;

	a1 = move(a2); // move assignment
	cout << "Let a1 = a2 by move assignment." << endl;
	cout << "Matrix a1 after move assignment: " << a1;
	cout << "Matrix a2 after move assignemtn: " << a2;

	// Demonstrate arithmetric operations on Matrix
	Matrix b1(2, 2, { 1,2, 3, 4 });
	Matrix b2(2, 2, { 1, 2, 3, 4 });

	cout << endl << "Demonstrate arithmetric operations on Matrix." << endl;
	cout << "Matrix b1:" << b1;
	cout << "Matrix b2:" << b2;
	cout << "b1 + b2 = " << b1 + b2;
	cout << "b1 - b2 = " << b1 - b2;
	cout << "b1 * b2 = " << b1 * b2;

	// Demonstrate member function that returns matrix with i th row and j th column deleted
	Matrix d1(3, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });

	cout << endl << "Demonstrate member function that returns matrix with ith row and j the column deleted." << endl;
	cout << "Matrix d1: " << d1;
	cout << "After deleting 2nd row and 2nd column of d1: " << d1.getDel(2, 2);
	
	// Demonstrate calculation of determinant of a matrix
	Matrix p1(3, 3, { 2, 3, 4, 2, 3, 2, 1, 1, 1 });
	cout << endl << "Determonstrate calculation of determinant of a square matrix." << endl;
	cout << "Matrix p1:" << p1;
	cout << "Determinant of p1:" << p1.getDet() << endl;

	//Let user input input a matrix and print it
	cout << "Demonstrate input of a matrix." ;
	cout << endl << "The format to input a matrix is: `no. of rows no. of columns  A_11 A_12 ... A_21 A_22...A_ij..`. " << endl;
	cout << "For example, to input a matrix" << E ;
	cout << "enter 2 2 1 2 3 4 and press CTRL+D and ENTER." << endl;

	Matrix r1;
	cout << "Now enter a matrix: ";
	cin >> r1;
	cout << "You entered:" << r1;


	system("pause");
	return 0;
}
