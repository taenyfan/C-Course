// This program stores and sorts inputs of the titles of different physics courses.
// Input course title in the following format(example) : 30392 Cosmology


#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib> // for exit()

using namespace std;


// Define struct to store full information of course
struct course {
	int courseNumber;    // store course number
	string courseName;   // store course name
	string courseTitle;  // store course title (course number + course name)
};


// Comparator function to sort by courseName alphabetically
bool compareName(const course& a, const course& b)
{
	return a.courseName < b.courseName;
}

// Comparator function to sort by courseNumber in ascending order
bool compareNumber(const course& a, const course& b)
{
	return a.courseNumber < b.courseNumber;
}


// Function that removes whitespaces from front and back of string. Returns trimmed string. 
// Use it like this: trim(string)
// Example: "    too much\t   \tspace\t\t\t  " --> "too much               space"
std::string trim(const std::string& str,
	const std::string& whitespace = " \t")
{
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

// Function that removes whitespaces from front and back of string and then reduce all consecutive whitespaces in string to 1 whitespace. Returns trimmed and reduced string.
// Use it like this: reduce(string). Needs to be used with trim function. 
// Example: "    too much\t   \tspace\t\t\t  " --> "too much space" 
// Example: " (  M )  a" --> "( M ) a"
std::string reduce(const std::string& str,
	const std::string& fill = " ",
	const std::string& whitespace = " \t")
{
	// trim first
	auto result = trim(str, whitespace);

	// replace sub ranges
	auto beginSpace = result.find_first_of(whitespace);
	while (beginSpace != std::string::npos)
	{
		const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
		const auto range = endSpace - beginSpace;

		result.replace(beginSpace, range, fill);

		const auto newStart = beginSpace + fill.length();
		beginSpace = result.find_first_of(whitespace, newStart);
	}

	return result;
}

/* Function that asks user for positive integer of year number
and returns that positive integer */
int getYear()
{

	int x;
	while (1)
	{
		cout << "Enter the year number to extract courses from:";
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
		if (x < 0)
		{
			cout << "Year number has to be positive. ";
			continue;
		}

		// Check if input is less than 10
		if (x > 9)
		{
			cout << "Year number has to be less than 10. ";
			continue;
		}

		break;
	}

	return x;
}


int main()
{
	const string degreeCode = "PHYS";

	// Vector of string to store course data 
	vector<string> degreeData;

	// Vector to store course information
	vector<course> degreeTitle;

	// Introduce user to program
	cout << "This program stores and sorts inputs of different PHYS courses.\nPlease input course title in the following format (example): 30392 Cosmology. " << endl;

	while (1)
	{
		// Temporary variables to store input from user
		int degreeNo=-1;      // degree number entered by user
		string degreeName;          // degree name entered by user
		string failedInput;         // failed input entered by user
		string tempdegreeTitle;         // combined degree number and degree name after successful input

		// Ask user for input of degreeNo and degreeName on a single line 
		cout << "Enter a course title (or x to finish): ";
		cin >> degreeNo; 

		// If user did not enter degreeNo first
		if (cin.fail()) // no extraction took place
		{
			cin.clear(); // reset to goodbit 

			getline(cin, failedInput); // get failedInput

			transform(failedInput.begin(), failedInput.end(), failedInput.begin(), ::tolower); // convert failedInput to lowercase

			failedInput.erase( remove(failedInput.begin(), failedInput.end(), ' ' ), failedInput.end()); // remove white spaces in failedInput

			// If failedInput is "x"
			if (failedInput == "x")
			{
				break;  // stop taking course names
			}

			cout << "Invalid Input. ";
			continue; // Ask user to enter course title again
		}

		// If degreeNo is negative
		if (degreeNo < 0)
		{
			cout << "Invalid Input. ";
			cin.ignore(9999, '\n'); // clear out the remaining input in the stream
			continue; // Ask user to enter course title again
		}

		// At this point, degreeNo input is successfull

		getline(cin, degreeName); // get degreeName (which is all the input after degreeNo)
		degreeName = reduce(degreeName); // reduce the extra whitespaces in degreeName

		// If input of degreeName is empty
		if (degreeName == "") // ask user to input course title 
		{
			cout << "Invalid input. ";
			continue;
		}

		// At this point, both degreeNo and degreeName input successfull

		// Combine degreeCode, degreeNo and degreeName into string tempdegreeTitle using stringstream
		stringstream ss; 
		ss << degreeCode << " " << degreeNo << " " << degreeName;  
		tempdegreeTitle = ss.str();

		// Store tempdegreeTitle into vector<string> degreeData
		degreeData.push_back(tempdegreeTitle);

		// Store int degreeNo, string degreeName and string tempdegreeTitle into vector<course> degreeTitle
		degreeTitle.push_back( {degreeNo, degreeName, tempdegreeTitle} );


	} 

	// Print out full course list in vector degreeData
	// If no courses entered, exit program
	if (degreeData.size() == 0) 
	{
		cout << "0 courses entered. Bye bye." << endl;
		system("pause"); // stop debugger window from closing immediately
		exit(1); // exit program
	}
	// If courses entered
	else
	{
		cout << degreeData.size() << " courses entered successfully." << endl; // display number of courses entered
		cout << "List of courses:" << endl;

		vector<string>::iterator it; 

		for (it = degreeData.begin(); it != degreeData.end(); it++)
		{
			cout << *it << endl;
		}

	}


	// Extract courses for a particular year
	int year;       // to store year number input
	vector<string> yearCourses; // to store courses of a particular year

	year = getYear();  // get user input for year number

	// Add appropriate courses from degreeTitles into yearCourses
	for (auto it = degreeTitle.begin(); it != degreeTitle.end(); it++)
	{
		string temp;   // string to store current entry in degreeTitle
		int temp4; // int to store sixth digit of current entry

		temp = (*it).courseTitle;  // extract current entry to temp

		stringstream ss; // extract first digit of current entry
		ss << temp[5];  
		ss >> temp4;


		if (temp4 == year)    // if first character in this entry of degreeTitle is same as int year
		{
			yearCourses.push_back(temp);      // add this entry into yearCourses
		}
	}

	// Print out entries in yearCourses
	//If yearCourses empty
	if (yearCourses.empty())
	{
		cout << "0 Year " << year << " courses found." << endl; 
	}
	//If yearCourses not empty
	else
	{
		cout << "List of Year " << year << " courses:" << endl;
		for (auto it = yearCourses.begin(); it != yearCourses.end(); it++)
		{
			cout << *it << endl;
		}
	}

	// Sort Courses by degreeNumber or degreeName in ascending order
	string numberOrName;   // to store input by user

	// Ask user for input for numberOrName (accpet either "number" or "name")
	while (1)
	{ 

		cout << "Sort by course number or name: ";
		getline(cin, numberOrName);   // get input for numberOrName

		numberOrName = reduce(numberOrName); // reduce numberOrName
		transform(numberOrName.begin(), numberOrName.end(), numberOrName.begin(), ::tolower); // convert numberOrName to lowercase

		// exit loop if input successful, continue if not
		if (numberOrName == "number") { break; }
		else if (numberOrName == "name") { break; }
		else { 
			cout << "Invalid input. ";
			continue;
		}
	}

	// Sort by degreeNumber if user entered "number"
	if (numberOrName == "number")
	{
		cout << "List of courses sorted by number: " << endl;
		sort(degreeTitle.begin(), degreeTitle.end(), compareNumber); // sort in ascending degreeNumber
		for (auto it = degreeTitle.begin(); it != degreeTitle.end(); it++)
		{
			cout << (*it).courseTitle << endl;
		}
		
	}

	// Sort by degreeName if user entered "name"
	else
	{
		cout << "List of courses sorted by name: " << endl;
		sort(degreeTitle.begin(), degreeTitle.end(), compareName);
		for (auto it = degreeTitle.begin(); it != degreeTitle.end(); it++)
		{
			cout << (*it).courseTitle << endl;
		}
	}
	

	system("pause"); // stop debugger window from closing immediately
	return 0;
}