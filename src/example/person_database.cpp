#include <person_database.h>
#include <fstream>			// We *could* have included this in person_database.h, but
							// didn't have to.  Putting it here is more "conservative" which
							// in this context is usually a good thing.
#include <sstream>
#include <iomanip>			// Necessary for std::setprecision
#include <iostream>


example::PersonDatabase::PersonDatabase(std::string fname) : mArray(nullptr), mFilename(fname),
															mArraySize(0)
{
	std::ifstream fp(mFilename);
	if (fp.is_open())
	{
		// We were able to open the file -- read in the data.  I'm relying on add_person
		// to do the hard work here
		unsigned int temp_id;
		float temp_rate;
		int temp_hours;
		std::string temp_fname;
		std::string temp_lname;

		//std::getline(fp, temp_fname);

		while (true)
		{
			// Get the data using stream input operator since they're space-delimited
			fp >> temp_id >> temp_rate >> temp_hours >> temp_fname >> temp_lname;

			if (fp.fail() || fp.eof())
			{
				// If we get here it means we weren't able to process the data above.
				// Since I control the file format, the assumption is this means we're out
				// of data
				break;
			}
			else
			{
				// We got valid data, so now build a Person and add it
				Person temp_person(temp_fname, temp_lname, temp_id, temp_rate);
				temp_person.set_hours_worked(temp_hours);

				// Note that when I call this, we're making a COPY of temp_person on the stack.  For
				// small objects like this, this is probably OK, but for larger objects it's much
				// better to use pointers (or references...which we'll look at in the next lab)
				add_person(temp_person);
				//std::cout << "Added person: " << temp_fname << " " << temp_lname << " " << temp_id << " " << temp_hours << " " << temp_rate << "\n";
			}
		}

		// Close the file
		fp.close();
	}
}



example::PersonDatabase::~PersonDatabase()
{
	// Write out the data to the file
	std::ofstream fp(mFilename);
	for (unsigned int i = 0; i < mArraySize; i++)
	{
		Person p = mArray[i];
		fp << p.get_id() << " " << p.get_rate() << " " << p.get_hours_worked() << " " << p.get_first_name();
		fp << " " << p.get_last_name() << "\n";
	}
	fp.close();

	// Free up the memory.  Note: you do NOT have to free non-dynamically allocated
	// attribute values (like mArraySize).  You can optionally set these back to default values
	// BUT, we normally only get to the destructor if our instance is being destroyed, so this
	// is probably not necessary either
	delete[] mArray;
}




void example::PersonDatabase::add_person(Person p)
{
	// In this lab, we're taking a naive approach -- each time we add a new Person using this
	// method, we re-allocate the array to be JUST big enough.  This is kind of costly especially
	// as we get a lot of things in the array

	if (mArray == nullptr)
	{
		// This is the first item we're adding
		mArray = new Person[1];
	}
	else
	{
		// See if that person already exists -- if we raise an exception it'll get us out of this
		// function
		for (unsigned int i = 0; i < mArraySize; i++)
		{
			if (mArray[i].get_id() == p.get_id())
				throw std::runtime_error("Person with id " + std::to_string(p.get_id()) + " already exists!");
		}

		// We have data in the array so must copy it to a new larger array (as on the slides)
		// ...make a larger array
		Person* temp_array = new Person[mArraySize + 1];

		// ...copy over data from the old array
		for (unsigned int i = 0; i < mArraySize; i++)
			temp_array[i] = mArray[i];

		// ...free the old array
		delete[] mArray;

		// ...make mArray point to temp_array.  Note how temp_array (the variable) goes out of scope
		//    when I leave this else...which is fine...mArray will hold the address of the chunk of memory
		mArray = temp_array;
	}

	// Put the new person at the LAST spot in the array (I haven't incrementd mArraySize so
	// this value IS the index of the last spot). Note that C/C++ structs/classes copy each field when we
	// use the = operator this way.  In C++ we can re-define how this works (and will in a future lab)
	mArray[mArraySize] = p;

	// We now have one more item in the array -- account for it!  In this context, it doesn't matter if we
	// use prefix++ like this or postfix++ (prefix is often ever so slightly faster)
	++mArraySize;
}



unsigned int example::PersonDatabase::get_num_people()
{
	return mArraySize;
}



bool example::PersonDatabase::remove_person(unsigned int id)
{
	// First, make sure we have this item and store its index;
	unsigned int index = mArraySize;		// <- invalid index, on purpose!  A real index would
											//    be less than this amount.
	for (unsigned int i = 0; i < mArraySize; i++)
	{
		if (mArray[i].get_id() == id)
		{
			index = i;
			break;
		}
	}

	// Return false if we have an invalid index (we won't go any further in this
	// method than this point)
	if (index == mArraySize)
		return false;

	// Now I know that I need to resize the array.  If it's currently 1, we don't need
	//  an array
	if (mArraySize == 1)
	{
		delete[] mArray;
		mArray = nullptr;		// Unlike in the destructor, we DO want to reset our attributes....
		mArraySize = 0;			// ...here because we might use them again.
		return true;
	}
	else
	{
		// This is the more general case where we have to copy some data to a smaller array
		Person* temp_array = new Person[mArraySize - 1];
		for (unsigned int i = 0; i < index; i++)
			temp_array[i] = mArray[i];
		for (unsigned int i = index + 1; i < mArraySize; i++)
			temp_array[i - 1] = mArray[i];

		// ... now free up the old array
		delete[] mArray;

		// ...and make mArray point to the new smaller array
		mArray = temp_array;

		// ...and adjust our size
		--mArraySize;

		return true;
	}
}



std::string example::PersonDatabase::to_string()
{
	std::stringstream ss;

	// This makes future floating point numbers always show the decimal and have 2 decimal places.
	// THIS kind of thing is OK to use (document it like I am below).  A simple reference check like
	// this is much different than using a LLM to generate portions of your code.
	// Reference: https://stackoverflow.com/questions/22515592/how-to-use-setprecision-in-c
	ss << std::setprecision(2) << std::fixed;

	float total = 0.0f;

	ss << "Person\tID\tHours\tRate\tMonthly Salary\n";
	ss << "======\t==\t=====\t====\t==============\n";
	for (unsigned int i = 0; i < mArraySize; i++)
	{
		Person p = mArray[i];
		ss << p.get_name(false) << "\t" << p.get_id() << "\t" << p.get_hours_worked() << "\t$";
		float s = p.get_salary();
		ss << p.get_rate() << "\t$" << s << "\n";
		total += s;
	}
	for (unsigned int i = 0; i < 11; i++)
		ss << "===";
	ss << "Total: $" << total << "\n";

	return ss.str();
}