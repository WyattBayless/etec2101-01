#include <person_database.h>
#include <person.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

example::PersonDatabase::PersonDatabase(std::string fname)
{
	// Initialize attributes
	my_array = nullptr;			// This means we (right now) don't have data
	my_array_size = 0;
	temp_array = nullptr;
	int check = 0;

	// Open the file

	std::ifstream fin(fname);
	if (!fin.is_open())
	{
		std::cout << "Error opening file '" << fname << "'\n";
		return;
	}

	//Read through the file, line-by-line
	while (true)
	{
		// Get a line's worth of data
		int temp_id;
		std::string temp_fname, temp_lname;
		float temp_hourly_rate;
		unsigned int temp_hours;

		// <code to read into those>
		// Reads each element, seperated by commas

		fin >> temp_id;
		fin.ignore(1000, ':');
		std::getline(fin, temp_fname);
		fin.ignore(1000, ':');
		std::getline(fin, temp_lname);
		fin.ignore(1000, ':');
		fin >> temp_hourly_rate;
		fin.ignore(1000, ':');
		fin >> temp_hours;
		fin.ignore(1000, '\n');


		std::cout << "Values read in:\n\tID=" << temp_id << "\n\tfname=" << temp_fname << "\n\tlname='" << temp_lname << "'\n";


		// <code to decide if its read properly>
		if (!fin.fail())
		{
			example::Person temp_person(temp_id, temp_fname, temp_lname);
			temp_person.set_hourly_rate(temp_hourly_rate);
			temp_person.set_hours_worked(temp_hours);

			// Use our add_person to do the hard work
			add_person(temp_person);

			std::cout << "here\n";
		}

		if (fin.eof())
		{
			break;
		}
	}
	// Close the file
	fin.close();
}

example::PersonDatabase::~PersonDatabase()
{
	// Come back to this
}

void example::PersonDatabase::add_person(example::Person p)
{
	// Case1: nothing in the array
	//		Code: make an array of size 1 and put p in the only spot
	if (my_array_size == 0)
	{
		my_array = new Person[1];
		my_array[0] = p;
		my_array_size = 1;
	}

	// Case2: array is already there (slide 16)
	//		Code: Make an array of my_array_size + 1
	//			  Code data from existing array to that new array
	//			  Free up the old array
	//			  Make my_array point to the larger array
	//			  Make the size one bigger
	//			  Put p into the last spot in that array
	else
	{
		//Rework to function more like Case2 description
		temp_array = new Person[my_array_size + 1];
		for (unsigned int i = 0; i < my_array_size; i++)
		{
			temp_array[i] = my_array[i];
		}
		delete[] my_array;
		my_array = temp_array;
		my_array[my_array_size] = p;
		my_array_size++;
	}
}

bool example::PersonDatabase::remove_person(unsigned int id_to_remove)
{
	bool found = false;
	unsigned int index;
	for(unsigned int i=0; i<my_array_size;i++)
	{
		if (my_array[i].get_id() == id_to_remove)
		{
			found = true;
			index = i;
			break;
		}
	}
	if (!found)
		return false;
}