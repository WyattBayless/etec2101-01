#include <person_database.h>

example::PersonDatabase::PersonDatabase(std::string fname);
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
		std::string temp_fname, temp lname;
		float temp_hourly_rate;
		unsigned int temp_hours;

		// <code to read into those>

		// <code to decide if its read properly>
		if (? ? ? )
		{
			Person temp_person(temp_id, temp_fname, temp_lname);
			temp_person.set_hourly_rate(temp_hourly_rate);
			temp_person.set_hours_worked(temp_hours);
		}
	}
}