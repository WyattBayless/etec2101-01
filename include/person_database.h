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

		//Person my_data[100]		// No! Can't go over
									// 100 entires

	public:
		// This method should open the file, probably
		// reading in one person per line like this
		// 101 John Doe 42 13.5
		// 102 Sally Smith 18 19.75
		example::PersonDatabase(std::string fname);

		// Adds a person
		void add_person(Person p);
	};

}



