// Wyatt Bayless
// ETEC2101-01
// Lab 01

#include <person.h>
#include <person_database.h>
#include <iostream>

// Note: Addressing what the labs specs say, I have the ssuds project with everything properly organized (hopefully),
//		 the Github repo, the Person Database class with all the methods, a main program that creates a Person Database
//		 and runs through a loop, and the columns in to_string line up decently well. I didn't get around to doing the doxygen
//		 stuff, but then again there are more points available then needed so that should be ok. 

int main(int argc, char** argv)
{
	// In this constructor, you'll read in the contents of the
	// text file into an array of Person objects. DO NOT use any
	// container types (std::vector, std::list, etc.)

	// Each person in persondb should have their own line, with information
	// in the order of ID number, First Name, Last Name, Hourly Rate, and then Hours worked.
	// Each element should be seperated by a colon
	example::PersonDatabase PD("..\\..\\media\\persondb.txt");

	int option;
	while (true) 
	{
		// Options
		std::cout << "1. Add a Person\n";
		std::cout << "2. Remove a Person\n";
		std::cout << "3. Print Database\n";
		std::cout << "4. Quit\n\n";
		std::cout << "Choose an option (input number option and press ENTER)\n\n";
		std::cin >> option;

		// Bad option inputted
		if (std::cin.fail() || option > 4) 
		{
			std::cout << "Invalid option. Please Try Again\n\n";
			std::cin.clear();
			continue;
		}

		//Add a Person
		if (option == 1)
		{
			// Get a line's worth of data
			unsigned int temp_id;
			std::string temp_fname, temp_lname;
			float temp_hourly_rate;
			unsigned int temp_hours;

			// User Inputs all data
			// This looks long but it's mainly just to check each input for misinputs.
			// If the user misinputs once they get to try again. If twice they return to Main Menu

			std::cout << "\nEnter ID Number:";
			std::cin >> temp_id;
			if (std::cin.fail()) 
			{
				std::cout << "\nInvalid Input. Please Input a Positive Integer\n";
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cout << "Enter ID Number:";
				std::cin >> temp_id;
				if (std::cin.fail())
				{ 
					std::cout << "\nReturning to Main Menu. Please use correct inputs next time.\n";
					std::cin.clear();
					std::cin.ignore(100, '\n');
					continue;
				}
			}
			std::cout << "Enter First Name:";
			std::cin >> temp_fname;
			if (std::cin.fail())
			{
				std::cout << "\nInvalid Input. Please Input a proper first name\n";
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cout << "Enter First Name:";
				std::cin >> temp_fname;
				if (std::cin.fail())
				{
					std::cout << "\nReturning to Main Menu. Please use correct inputs next time.\n";
					std::cin.clear();
					std::cin.ignore(100, '\n');
					continue;
				}
			}
			std::cout << "Enter Last Name:";
			std::cin >> temp_lname;
			if (std::cin.fail())
			{
				std::cout << "\nInvalid Input. Please Input a proper last name\n";
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cout << "Enter Last Name:";
				std::cin >> temp_lname;
				if (std::cin.fail())
				{
					std::cout << "\nReturning to Main Menu. Please use correct inputs next time.\n";
					std::cin.clear();
					std::cin.ignore(100, '\n');
					continue;
				}
			}
			std::cout << "Enter Hourly Rate:";
			std::cin >> temp_hourly_rate;
			if (std::cin.fail())
			{
				std::cout << "\nInvalid Input. Please Input a Number\n";
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cout << "Enter Hourly Rate:";
				std::cin >> temp_hourly_rate;
				if (std::cin.fail())
				{
					std::cout << "\nReturning to Main Menu. Please use correct inputs next time.\n";
					std::cin.clear();
					std::cin.ignore(100, '\n');
					continue;
				}
			}
			std::cout << "Enter Hours Worked:";
			std::cin >> temp_hours;
			if (std::cin.fail())
			{
				std::cout << "\nInvalid Input. Please Input a Positive Integer\n";
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cout << "Enter Hourly Rate:";
				std::cin >> temp_hours;
				if (std::cin.fail())
				{
					std::cout << "\nReturning to Main Menu. Please use correct inputs next time.\n";
					std::cin.clear();
					std::cin.ignore(100, '\n');
					continue;
				}
			}

			std::cout << "\nThanks for the Input\n";	// This is a nice touch, but was really added to prevent a bug in the Hours Worked misinput handling

			// Create a Person
			example::Person temp_person(temp_id, temp_fname, temp_lname);
			temp_person.set_hourly_rate(temp_hourly_rate);
			temp_person.set_hours_worked(temp_hours);

			// Add Person to Database
			PD.add_person(temp_person);

			std::cout << "\nPerson added\n\n";
		}

		// Removes a Person
		if (option == 2)
		{
			unsigned int temp_id;

			// Get user inputted ID and check for misinput
			std::cout << "\nEnter ID Number:";
			std::cin >> temp_id;
			std::cout << "\nInvalid Input. Please Input a Positive Integer\n";
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cout << "Enter ID Number:";
				std::cin >> temp_id;
				if (std::cin.fail())
				{
					std::cout << "\nReturning to Main Menu. Please use correct inputs next time.\n";
					std::cin.clear();
					std::cin.ignore(100, '\n');
					continue;
				}
			}

			//Remove Person from Database
			PD.remove_person(temp_id);

			std::cout << "\nPerson Removed\n\n";
		}

		if (option == 3)
		{
			std::string temp_string;

			// Call the to_string function into a temp_string
			temp_string = PD.to_string();

			// Output the temp_string to the screen
			std::cout << "\n";
			std::cout << temp_string;
		}

		if (option == 4)
		{
			// break out of while loop and quit
			break;
		}
	}
	return 0;
}