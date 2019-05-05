// Created: Jiachen 14 Feb 2019
// PHYS 30762 C++ Assignment 2

// Program to read in numerical data from a data file and compute the mean, standard deviation
// and standard error of the mean in units of electronic charge C. 
// Note: Data file is arranged in lines, with each line containing either a data value or a 
// rogue word. Program skips and ignores rogue words. 

#include <iostream>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <cmath> 
#include <cstdlib> // for exit()
#include <new>
#include <string>

using namespace std;

// Function that returns mean of the elements of an array of arbitrary size
double getMean(double *arry, int dataCount)
{
	double sum = 0;
	double mean;

	for (int j = 0; j < dataCount; j++)
	{
		sum = sum + arry[j];
	}

	mean = sum / dataCount;

	return mean;
}

// Function that returns standard deviation of the elements of an array of arbitrary size
double getStd(double *arry, int dataCount)
{
	//Calculate mean
	double sum = 0;
	for (int j = 0; j < dataCount; j++)
	{
		sum = sum + arry[j];
	}
	double mean = sum / dataCount;

	// Calculate sum of (x_i - mean)^2
	double preStd = 0;
	for (int j = 0; j < dataCount; j++)
	{
		preStd = preStd + pow((arry[j] - mean), 2);
	}

	// Calculate standard deviation
	double std;
	std = sqrt( (1 / ( static_cast<double>(dataCount) -  1 ) ) * preStd);

	return std;

}

// Main program
int main()
{
	// Ask use to input file name
	string filename;
	cout << "Enter file name of data file in the format xxx.dat or xxx.txt: ";
	cin >> filename;

	// Read in data from file
	ifstream myfile2; 
	myfile2.open (filename);

	// Print error and exit if file not opened
	if (!myfile2.is_open())
	{
		cerr << "Error. Could not open data file for reading! Exiting." << endl;
		system("pause"); // stop debugger window from closing immediately
		exit(1);
	}

	// Count number of numerical data in file
	int dataCount = 0; // variable to count number of numerical data

	int w = 0;    // variable that counts number of rogue words

	while (!myfile2.eof())
	{
		double x;         // variable that stores a temporary data point            
		myfile2 >> x;    // extract a data from myfile2 stream

		// check if data is of the form abc, abc45, %^ etc
		if (myfile2.fail()) // no extraction took place
		{
			myfile2.clear(); // reset to goodbit so can use .ignore()
			myfile2.ignore(numeric_limits<streamsize>::max(), '\n'); // clear out the remaining data in the stream until '\n'
			w++; 
			continue;  // do nothing with temp data and start reading next data
		}
	
		dataCount++; // count up if x successfully extracted

	}

	// Print warning if rogue words found in file
	if (w == 2 )
	{
		cout << "Warning! Rogue word found in data file!" << endl;
	}
	if (w > 2)
	{
		cout << "Warning! Rogue words found in data file!" << endl; 
	}

	// Create dynamic array to read in data from file
	double *mk2;
	mk2 = new (nothrow) double [dataCount]; 

	if (mk2 == nullptr)    // if memory allocation fails
	{
		cerr << "Error assigning memory. Please take measures. Exiting." << endl;
		exit(1);
	}

	// Set position of next extraction to beginning of myfile2 stream
	myfile2.clear(); // clear eof flag
	myfile2.seekg(0); 

	// Read in data from file into dynamic array
	int i = 0;         // variable that counts the position of mk2 array

	while (!myfile2.eof())
	{
		double x;         // variable that stores a temporary data point
		myfile2 >> x;    // extract a data from myfile2 stream

		// check if data is of the form abc, abc45, %^ etc
		if (myfile2.fail()) // no extraction took place
		{
			myfile2.clear(); // reset to goodbit so can use .ignore()
			myfile2.ignore(numeric_limits<streamsize>::max(), '\n'); // clear out the remaining data in the stream until '\n'
			continue;  // do nothing with temp data and start reading next data
		}

		mk2[i] = x;  // assign successfully extracted x into an array element
		i++;
	}

	// Dynamic array formed. Close file.
	myfile2.close();

	// Print array data
	cout << dataCount << " data are extracted successfully." << endl;
	cout << "The data extracted are: ";
	for (int j = 0; j < dataCount; j++)
	{
		cout << mk2[j] << '\t';
	}
	cout << '\n';

	// Calculate mean of array data
	double mean = getMean(mk2, dataCount);

	// Calculate standard deviation of array data
	double std = getStd(mk2, dataCount);

	// Calculate standard error in mean
	double stdMean = std / sqrt(dataCount);

	// Print mean value
	cout << "The calculated mean is: " << scientific << setprecision(5) << mean << " C" << endl;

	// Print standard deviation value
	cout << "The calculated standard deviation is: " << scientific << setprecision(5) << std << " C" << endl;

	// Print standard error of mean
	cout << "The calculated standard error of the mean is: " << scientific << setprecision(5) << stdMean << " C" << endl;

	// Free memory
	delete[] mk2;

	system("pause"); // stop debugger window from closing immediately
	return 0;
}

