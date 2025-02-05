#include <person_database.h>
#include <person.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#define FNAME "..\\..\\media\\persondb.txt"  // I tried putting the fname string into a 
											 // new attribute string, since we can't pass 
											 // an argument to the destructor, so that I could
											 // access the file name string but it wasn't 
											 // working. This is the solution I could make work

example::PersonDatabase::PersonDatabase(std::string fname)
{
	// Initialize attributes
	my_array = nullptr;			// This means we (right now) don't have data
	my_array_size = 0;
	temp_array = nullptr;

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
		unsigned int temp_id;
		std::string temp_fname, temp_lname;
		float temp_hourly_rate;
		unsigned int temp_hours;

		// <code to read into those>
		// Reads each element, seperated by colons

		fin >> temp_id;
		fin.ignore(1000, ':');
		std::getline(fin, temp_fname,':');
		std::getline(fin, temp_lname,':');
		fin >> temp_hourly_rate;
		fin.ignore(1000, ':');
		fin >> temp_hours;


		// <code to decide if its read properly>
		if (!fin.fail())
		{
			example::Person temp_person(temp_id, temp_fname, temp_lname);
			temp_person.set_hourly_rate(temp_hourly_rate);
			temp_person.set_hours_worked(temp_hours);

			// Use our add_person to do the hard work
			add_person(temp_person);
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
	std::cout << my_array_size;
	std::cout << FNAME;

	std::ofstream fout(FNAME);
	for (unsigned int i = 0; i < my_array_size; i++)
	{
		fout << my_array[i].get_id() << ":" << my_array[i].get_first_name() << ":" 
			 << my_array[i].get_last_name() << ":" << my_array[i].get_hourly_rate() << ":"
			 << my_array[i].get_hours_worked() << "\n";
	}
	//delete[] my_array;  // having delete for this caused an error, 
						  // I suppose because it gets deleted as part of add_person
						  // and then points to temp_array
	delete[] temp_array;

	fout.close();
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
			if (my_array[i].get_id() == p.get_id())
			{
				std::runtime_error("ID Number already exists");
			}
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

	// Make a temp_array (one smaller)
	// Copy data before index
	// Copy data after index
	// Free up old array
	// Make my_array point to smaller array 
	// Decrement my_array_size 

	temp_array = new Person[my_array_size - 1];
	for (unsigned int i = 0;i < my_array_size;i++)
	{
		if (i != index)
		{
			temp_array[i] = my_array[i];
		}
	}
	delete[] my_array;
	my_array = temp_array;
	my_array_size--;
}

int example::PersonDatabase::get_num_people()
{
	return my_array_size;
}

