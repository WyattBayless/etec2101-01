#include <iostream>
#define PERSON_DATABASE_USE_NEW_IMPLEMENTATION   // <- Added for bonus on Lab2.  Remove to use old impl.
#include <person_database.h>
#include <person.h>				// <- not necessary, but OK to (re-) include

// These macros and functions weren't necessary, but helped de-clutter the main
#define BIG_UINT std::numeric_limits<unsigned int>::max()
#define BIG_INT std::numeric_limits<unsigned int>::max()
#define MAX_INPUT_SIZE 1000

unsigned int input_uint(std::string prompt, std::string error_msg)
{
	unsigned int result;
	std::cout << prompt;
	std::cin >> result;
	if (std::cin.fail())
	{
		std::cout << error_msg;
		std::cin.clear();
		std::cin.ignore(MAX_INPUT_SIZE, '\n');
		return BIG_UINT;
	}
	else
		return result;
}

bool input_person(example::Person* in_ptr)
{
	unsigned int temp_id = input_uint("\tEnter ID: ", "Invalid integer\n");
	if (temp_id == BIG_UINT)
		return false;

	std::cout << "\tEnter Hourly Rate: ";
	float temp_rate;
	std::cin >> temp_rate;
	if (std::cin.fail())
	{
		std::cout << "Invalid float\n";
		std::cin.clear();
		std::cin.ignore(MAX_INPUT_SIZE, '\n');
		return false;
	}


	std::cout << "\tEnter Hours worked: ";
	int temp_hours;
	std::cin >> temp_hours;
	if (std::cin.fail())
	{
		std::cout << "Invalid integer\n";
		std::cin.clear();
		std::cin.ignore(MAX_INPUT_SIZE, '\n');
		return false;
	}

	std::cin.ignore(MAX_INPUT_SIZE, '\n');
	std::string temp_first_name, temp_last_name;
	std::cout << "\tEnter First Name: ";
	std::getline(std::cin, temp_first_name);
	//std::cin.ignore(MAX_INPUT_SIZE, '\n');
	//std::cin >> temp_first_name;
	//std::cin.ignore(MAX_INPUT_SIZE, '\n');
	std::cout << "\tEnter Last Name: ";
	//std::cin >> temp_last_name;
	std::getline(std::cin, temp_last_name);
	//std::cin.ignore(MAX_INPUT_SIZE);

	*in_ptr = example::Person(temp_first_name, temp_last_name, temp_id, temp_rate);
	in_ptr->set_hours_worked(temp_hours);

	return true;
}


int main(int argc, char** argv)
{
	bool show_menu = true;
	example::PersonDatabase PD("..\\..\\..\\media\\person_data.txt");
	unsigned int menu_choice = 200;

	while (menu_choice != 9)
	{
		// Show the menu if we need to
		if (show_menu)
		{
			std::cout << "PERSON DATABASE main menu\n=========================\n";
			std::cout << "1. Add a person\n2. Remove a person\n3. Generate report\n9. Quit\n\n";
			show_menu = false;
		}

		// Show a prompt and get the menu choice
		menu_choice = input_uint(">>> ", "Invalid menu choice\n\n");
		if (menu_choice == BIG_UINT)
			show_menu = true;

		// Now process each menu choice (note the quit case is handled by the while condition)
		example::Person temp_person;
		unsigned int temp_id;
		switch (menu_choice)
		{
		case 1:
			// Add Person
			if (input_person(&temp_person))
			{
				// I'm using exception-handling here to attempt to add.  If it fails (because we
				// have an invalid index#), just print an error message
				try
				{
					PD.add_person(temp_person);
				}
				catch (std::runtime_error e)
				{
					std::cout << e.what() << "\n";
				}
			}
			break;
		case 2:
			// Remove Person
			temp_id = input_uint("\tEnter ID: ", "Invalid Integer");
			if (PD.remove_person(temp_id))
				std::cout << "\tPerson with ID#" << temp_id << "successfully removed\n";
			else
				std::cout << "\tCould not find Person with ID#" << temp_id << "\n";
			break;
		case 3:
			// Generate Report
			std::cout << PD.to_string() << "\n";
			break;
		}
	}

	// Note that we don't have to do anything special to trigger the destructor -- when
	// PD goes out of scope, the destructor will be called for us.
}