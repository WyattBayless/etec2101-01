#include <person.h>
#include <person_database.h>
#include <iostream>

int main(int argc, char** argv)
{
	// In this constructor, you'll read in the contents of the
	// text file into an array of Person objects. DO NOT use any
	// container types (std::vector, std::list, etc.)

	// Each person in persondb should have their own line, with information
	// in the order of ID number, First Name, Last Name, Hourly Rate, and then Hours worked.
	// Each element should be seperated by a comma
	example::PersonDatabase PD("..\\..\\media\\persondb.txt");

	int option;
	while (true) 
	{
		std::cout << "1. Add a Person\n";
		std::cout << "2. Remove a Person\n";
		std::cout << "3. Print Database\n";
		std::cout << "4. Quit\n\n";
		std::cout << "Choose an option (input number option and press ENTER)\n\n";
		std::cin >> option;

		// Bad option input
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

			// This looks long but it's mainly just to check each input.

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
			// Error checking here wasn't working correctly like the others
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

			example::Person temp_person(temp_id, temp_fname, temp_lname);
			temp_person.set_hourly_rate(temp_hourly_rate);
			temp_person.set_hours_worked(temp_hours);

			PD.add_person(temp_person);

			std::cout << "\nPerson added\n\n";
		}

		if (option == 2)
		{
			unsigned int temp_id;
			std::cout << "\nEnter ID Number:";
			std::cin >> temp_id;
			if (std::cin.fail())
			{
				std::cout << "Invalid Input. Please Input a Positive Integer\n";
				std::cin.clear();
			}

			PD.remove_person(temp_id);

			std::cout << "\nPerson Removed\n\n";
		}

		if (option == 3)
		{
			// String stuff
		}

		if (option == 4)
		{
			break;
		}
	}
	return 0;
}