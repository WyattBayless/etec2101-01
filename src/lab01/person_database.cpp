#include <person_database.h>
#include <person.h>

example::PersonDatabase::PersonDatabase(std::string fname)
{
	// Initialize attributes
	my_array = nullptr;			// This means we (right now) don't have data
	my_array_size = 0;

	// Open the file

	//Read through the file, line-by-line
	while (? ? ? )
	{
		// Get a line's worth of data
		int temp_id;
		std::string temp_fname, temp_lname;
		float temp_hourly_rate;
		unsigned int temp_hours;

		// <code to read into those>

		// <code to decide if its read properly>
		if (? ? ? )
		{
			Person temp_person(temp_id, temp_fname, temp_lname);
			temp_person.set_hourly_rate(temp_hourly_rate);
			temp_person.set_hours_worked(temp_hours);

			// Use our add_person to do the hard work
			add_person(temp_person);
		}
	}
	// Close the file
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
	//		Code: Make an array of my_array_size = 1
	//			  Code data from existing array to that new array
	//			  Free up the old array
	//			  Make my_array point to the larger array
	//			  Make the size one bigger
	//			  Put p into the last spot in that array
	else
	{

	}

}