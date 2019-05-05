// C++ Assignment 1 
// Jiachen Guo 10090371

// Program to calculate transition energies using simple Bohr model#
// Formula used is transition energy = 13.6*(Z^2)*(1/n_j^2-1/n_i^2) eV
// where Z is the atomic number, n_j is the final principal quantum number, n_i is the 
// initial principle quantum number

#include<iostream>
#include<string>
#include<cmath>
#include<iomanip>
#include <algorithm>
using namespace std; 

//===================Define Functions======================================================================
/* Function that asks user for positive integer of atomic number 
and returns that positive integer */
int getZ()
{

	int x;
	while (1)
	{
		cout << "Enter the atomic number:";
		cin >> x;

		// Check if input is of the form abc, abc45, %^ etc
		if (cin.fail()) // no extraction took place
		{
			cin.clear(); // reset to goodbit so can use cin.ignore()
			cin.ignore(9999, '\n'); // clear out the remaining input in the stream
			cout << "Invalid Input. ";
			continue;
		}

		cin.ignore(9999, '\n'); // clear out remaining input in the stream

		// Check if input is of the form 234asd, 23^&34 etc
		if (cin.gcount() > 1){                   // cleared out some input including '\n' 
			cout << "Invalid Input. ";	
			continue; 
		}

		// Check is input is positive
		if (x <= 0) 
		{ 
			cout << "Atomic number has to be positive. ";
			continue; 
		}

		break;
	}

	return x;
}

/* Function that asks user for positive integer of initial quanutm number n_i
and returns that positive integer */
int getn_i()
{

	int x;
	while (1)
	{
		cout << "Enter the intial quantum number:";
		cin >> x;

		// Check if input is of the form abc, abc45, %^ etc
		if (cin.fail()) // no extraction took place
		{
			cin.clear(); // reset to goodbit so can use cin.ignore()
			cin.ignore(9999, '\n'); // clear out the remaining input in the stream
			cout << "Invalid Input. ";
			continue;
		}

		cin.ignore(9999, '\n'); // clear out remaining input in the stream

		// Check if input is of the form 234asd, 23^&34 etc
		if (cin.gcount() > 1){                   // cleared out some input including '\n' 
			cout << "Invalid Input. ";
			continue;
		}

		// Check is input is positive
		if (x <= 0)
		{
			cout << "Initial quantum number has to be larger than 0. ";
			continue;
		}

		break;
	}

	return x;
}

/* Function that asks user for positive integer of final quanutm number n_f
and returns that positive integer */
int getn_f()
{

	int x;
	while (1)
	{
		cout << "Enter the final quantum number:";
		cin >> x;

		// Check if input is of the form abc, abc45, %^ etc
		if (cin.fail()) // no extraction took place
		{
			cin.clear(); // reset to goodbit so can use cin.ignore()
			cin.ignore(9999, '\n'); // clear out the remaining input in the stream
			cout << "Invalid Input. ";
			continue;
		}

		cin.ignore(9999, '\n'); // clear out remaining input in the stream

		// Check if input is of the form 234asd, 23^&34 etc
		if (cin.gcount() > 1){                   // cleared out some input including '\n' 
			cout << "Invalid Input. ";
			continue;
		}

		// Check is input is positive
		if (x <= 0)
		{
			cout << "Final quantum number has to be larger than 0. ";
			continue;
		}

		break;
	}

	return x;
}

/* Function that asks user for string input of J or eV
and returns either j or ev */
string getUnits()
{
	string x; 

	while (1)
	{
		cout << "Do you want the transition energy in Joules or electron-volts? Type j for Joules and ev for electron-volts:";
		cin >> x; 

		transform(x.begin(), x.end(), x.begin(), ::tolower); // convert x to lowercase

	
		if (x=="j") // user entered "j"
		{
			cout << "Ok, the transition energy will be displayed in Joules. \n";
			return x;
		}

		if (x=="ev") // user entered "ev"
		{
			cout << "Ok, the transition energy will be displayed in electron-volts. \n";
		    return x; 
		}

		else // user entered something else
		{
			cout << "Invalid input. ";
			continue;
		}
	}

}

/* Function that takes positive integer inputs of z, n_i, n_f and string input of units
and returns transition energy in Joules if units == "j" or in eV if units =='ev'*/
double getEnergy(int z, int n_i, int n_f, string units)
{
	double energy;

	energy = 13.6 * pow(z, 2) * ((1 / pow(n_f, 2)) - (1 / pow(n_i, 2)));

	if (units == "ev")
	{
		return energy;
	}

	if (units == "j")
	{
		return energy*1.60*pow(10, -19);
	}

	else return -1; // will not happen. if happens, sth wrong with code
}

/* Function that asks user for string input of y or n
and returns either "y" or "n" */
string getRepeat()
{
	string x;

	while (1)
	{
		cout << "Do you want to do another calculation? Type y for yes and n for no.";
		cin >> x;

		transform(x.begin(), x.end(), x.begin(), ::tolower); // convert x to lowercase

		if (x == "y") // user entered "j"
		{
			return x;
		}

		if (x == "n") // user entered "ev"
		{
			return x;
		}

		else // user entered something else
		{
			cout << "Invalid input. ";
			continue;
		}
	}

}

//===================End of Functions================================================================



//===========================Main Program=============================================================
int main()
{
	// Introduce user to program
	cout << "This program calculates the transition energies of the simple Bohr model." << endl;

	while (1)
	{

		// Declare variables
		int z; // atomic number
		int n_i; // initial principal quantum number
		int n_f; // final principal quantum number
		string units; // energy in J or eV
		double E; // transition energy (in either J or eV)
		string repeat; // string that takes 'y' to repeat program and 'n' to terminate program

		// Get input for z
		z = getZ();


		// Get input for n_i, n_f and check that n_i > n_f
		while (1)
		{
			n_i = getn_i();
			n_f = getn_f();

			// check if n_i > n_f
			if (n_i < n_f)
			{
				cout << "Initial principal quantum number should be larger than final principal quantum number. Please try again. \n";
				continue;
			}

			else break;
		}

		// Get input for units
		units = getUnits();

		// Calculate transition energy in J or eV
		E = getEnergy(z, n_i, n_f, units);

		// Display the transition energy
		if (units == "j")
		{
			cout << "The transition energy is " << scientific << setprecision(4) << E << " Joules, to 5 significant figures. \n";
		}

		if (units == "ev")
		{
			cout << "The transition energy is " << scientific << setprecision(4) << E << " eV, to 5 significant figures. \n";
		}

		// Ask user if want to repeat calculation
		repeat = getRepeat();

		if (repeat == "n")
		{
			cout << "Bye bye. \n";
			break;
		}
	}

	return 0; 
}
//========================================End of Main Program====================================================