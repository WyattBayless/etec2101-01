#include <person.h>

namespace example
{
	class PersonDatabase
	{
	private:
		// int* temp;		// Does temp point to a single int?
		// int x = 70;
		// temp = &x;
		// temp = (int*)malloc(sizeof(int) * 100); // an array of 100 ints
		// temp[0] = 77;
		// temp[1] = 78;
									// Or an array?
									// Could be both

		Person* my_array;			// This WILL hold (eventually)
		// an array of Person objects.
		unsigned int my_array_size; // The size of the my_array array

		Person* temp_array;			// Temp array for later

	public:
		// This method should open the file, probably
		// reading in one person per line like this
		// 101 John Doe 42 13.5
		// 102 Sally Smith 18 19.75
		PersonDatabase(std::string fname);

		~PersonDatabase();

		// Adds a person
		void add_person(example::Person p);

		// Removes a person
		bool remove_person(unsigned int id_to_remove);

		// Returns the number of people in database
		int get_num_people();

		// Returns a string of all data in database for printing
		std::string to_string();

	};

}



