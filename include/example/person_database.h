// array_list.h
#pragma once
#include <string>
#include <person.h>
#ifdef PERSON_DATABASE_USE_NEW_IMPLEMENTATION
#include <array_list.h>								// We only need this if using new impl.
#endif


namespace example
{
	/// <summary>
	/// A "smart array" of Person objects.  Our ArrayList class (Lab2+) will generalize a lot
	/// of what we have started here.
	/// </summary>
	class PersonDatabase
	{
	protected:
		/// <summary>
		/// The filename we are reading from (in the constructor) or saving to (in the destructor)
		/// </summary>
		std::string mFilename;

#if !PERSON_DATABASE_USE_ORIGINAL_IMPLEMENTATION
		/// <summary>
		/// The actual array of Person objects we're holding at the moment.
		/// </summary>
		Person* mArray;

		/// <summary>
		/// The size of the mArray array -- in C/C++ you must store this yourself unless
		/// using std::Vector, ssuds::ArrayList, etc.
		/// </summary>
		unsigned int mArraySize;
#else
		/// <summary>
		/// The internal ArrayList used to hold all People objects
		/// </summary>
		ssuds::ArrayList<example::Person> mArrayList;
#endif
		
	public:
		/// <summary>
		/// This constructor attempts to load people object from the given file.
		/// </summary>
		/// <param name="fname">The (relative path) and filename of the data file</param>
		PersonDatabase(std::string fname);

		/// <summary>
		/// The destructor
		/// </summary>
		~PersonDatabase();

		/// <summary>
		/// Makes the internal array one bigger to accomodate this new person.  This method
		/// throws a std::runtime_error exception if that id already exists.
		/// </summary>
		/// <param name="p">A *COPY* of a Person object defined elsewhere</param>
		void add_person(Person p);


		/// <summary>
		/// Returns the number of people in the database (i.e. the size of the internal array)
		/// </summary>
		/// <returns>The number of people in the database</returns>
		unsigned int get_num_people();


		/// <summary>
		/// Attempts to remove a person with the given id#. 
		/// </summary>
		/// <param name="id">The ID of the person to remove</param>
		/// <returns></returns>
		bool remove_person(unsigned int id);


		/// <summary>
		/// Generates a summary report string
		/// </summary>
		/// <returns>a large string containing the report</returns>
		std::string to_string();
	};
}
