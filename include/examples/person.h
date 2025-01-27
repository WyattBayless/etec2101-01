//The #pragme once is a short-hand for the #ifndef/#define/.../#endif thing
//The purpose of both is to prevent the compiler from ever seeing the declaration
//of this class twice (which would cause an error)

#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>

// Make Person a part of the example namespace
// put additional things in the same namespace in other files
// by doing the same thing we have here
namespace example
{
	/// <summary>
	/// This is a class that illustrates how to use OOP concepts in C++
	/// </summary>
	class Person
	{
		//By default everything [attributes and methods] is PRIVATE (we can only access it in the class)
		// Good rule of thumb make attributes private and have methods to INDIRECTLY
		// access them public.
	private:
		//ATTRIBUTES -- A variable that all instance of the class have
		int id;
		std::string first_name;
		std::string last_name;
		float hourly_rate;
		unsigned int hours_worked;

	public:
		// Constructor

		/// <summary>
		/// This is the default constructor for the Person class
		/// </summary>
		Person();

		Person(int starting_id, std::string start_fname, std::string start_lname);

		//Destructor (called when an instance is about to be destroyed)
		~Person();   // Always has the name of the class. Only one!!

		//GETTER methods
		int get_id();
		std::string get_first_name();
		std::string get_last_name();
		float get_hourly_rate();
		unsigned int get_hours_worked();

		//SETTER methods
		void set_hourly_rate(float new_rate);
		void set_hours_worked(unsigned int new_hours);

		//METHOD -- a function that instances of the class can call
		/// <returns> The wage for this person is returned here </return>
		float calculate_wage();
	};
}

#endif