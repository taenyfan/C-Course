// PHYS 30762 Progamming in C++
// Assignment 4

// Simple demonstration of a C++ class

// Hubble types: E[0-7], S0, S[a-c], SB[a-c], Irr
// Redshift z in range [0,10]
// Total mass M_tot in range [1e7, 1e12] M_sun
// Stellar mass fraction f_* in range [0,0.05]

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Define class Galaxy
class Galaxy
{
private:
	string m_name;
	string m_hubbleType;
	double m_redshift;
	double m_totalMass;
	double m_stellarMassFraction;
	vector<Galaxy> m_satellites; 

public:
	Galaxy() // default constructor
	{
		m_name = "X";
		m_hubbleType = "X";
		m_redshift = 0;
		m_totalMass = 0;
		m_stellarMassFraction = 0;
	}

	Galaxy(string name, string hubbleType, double redshift, double totalMass, double stellarMassFraction) // parameterized constuctor
	{
		m_name = name;
		m_hubbleType = hubbleType;
		m_redshift = redshift;
		m_totalMass = totalMass;
		m_stellarMassFraction = stellarMassFraction;
	}

	~Galaxy() // destructor
	{
		cout << "deleting Galaxy" << endl;
	}

	void print();  // forward declaration for member function to print out Galaxy data

	void setType(string hubbleType) // member function to change hubble type of Galaxy
	{
		m_hubbleType = hubbleType; 
	}

	double returnStellarMass(double stellarMassFraction, double totalMass) // member function to return the stellar mass 
	{
		return stellarMassFraction*totalMass; 
	}

	void addSatellite(string name, string hubbleType, double redshift, double totalMass, double stellarMassFraction) //member function to add a satellite galaxy to vector<Galaxy> m_satellites
	{
		Galaxy satellite(name, hubbleType, redshift, totalMass, stellarMassFraction); // create Galaxy object satellite
		m_satellites.push_back(satellite); // append object satellite into vector m_satellites
	}

};

// Function declarations
void Galaxy::print()  // member function of Class Galaxy that prints out the Galaxy data
{
	cout << endl;
	cout << m_name << " data:" << endl;
	cout << "Hubble Type: " << m_hubbleType << endl;
	cout << "Redshift: " << m_redshift << endl;
	cout << "Total Mass: " << m_totalMass << " Solar Mass"<< endl;
	cout << "Stellar Mass Fraction: " << m_stellarMassFraction << endl;
	cout << "Stellar Mass: " << returnStellarMass(m_stellarMassFraction, m_totalMass) << " Solar Mass"<< endl; 
	
	if (m_satellites.empty())
	{
		cout << "No. of satellites: 0." << endl;
	}
	else
	{
		cout << "No. of satellites: " << m_satellites.size() << endl;
		for (auto it = m_satellites.begin(); it != m_satellites.end(); it++)
		{
			(*it).print();
		}
	}
}

// Main program
int main()
{
	// Vector of Galaxy
	vector<Galaxy> galaxies;

	// Construct galaxy A
	Galaxy A; // creates Galaxy A by calling default constructor Galaxy()

	// Construct galaxy B using direct intialization
	Galaxy B("B", "E0", 1, 1e8, 0.01); // creates Galaxy B by calling parameterized constructor Galaxy()
	B.setType("E1"); // change the hubble type of B

	// Construct galaxy C  using uniform initialization
	Galaxy C{ "C", "S0", 9, 1e10, 0.04 };

	// Add two satellite galaxies to C
	C.addSatellite("Satellite 1", "Irr", 2, 1e8, 0.01);
	C.addSatellite("Satellite 2", "SBc", 3, 1e9, 0.03);

	// Append galaxies A, B, C into vector<Galaxy> galaxies
	galaxies.push_back(A);
	galaxies.push_back(B);
	galaxies.push_back(C);

	// Print out the data for all galaxy entries in vector galaxies
	for (auto it = galaxies.begin(); it != galaxies.end(); it++)
	{
		(*it).print();
	}

	system("pause");
	return 0;
}