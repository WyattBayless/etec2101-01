#pragma once
#include <string>

namespace example
{
	/// <summary>
	/// This is a simple class we'll use to explore basic C++ OOP 
	/// (Object-Oriented Programming) concepts.  It's not very useful
	/// in and of itself.
	/// </summary>
	class Person
	{
	protected:
		/// <summary>
		///  This is the Person's first name
		/// </summary>
		std::string mFirstName;

		/// <summary>
		/// This is the Person's last name
		/// </summary>
		std::string mLastName;

		/// <summary>
		/// This is a (unique) ID assigned to this person
		/// </summary>
		unsigned int mID;

		/// <summary>
		/// The hours worked this pay period (could be negative)
		/// </summary>
		int mHoursWorked;

		/// <summary>
		/// The rate (in dollars) per hour of this person
		/// </summary>
		float mHourlyRate;

	public:
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@ CONSTRUCTORS / OPERATORS        @
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		/// <summary>
		/// The DEFAULT CONSTRUCTOR
		/// </summary>
		Person();

		/// <summary>
		/// This method isn't really necessary to define in this class since we have no cleanup to do
		/// </summary>
		~Person();


		/// <summary>
		/// This is a constructor that takes initial values for most of the attributes
		/// </summary>
		Person(std::string starting_fname, std::string starting_lname, unsigned int id, float starting_rate);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@ GETTERS / SETTERS               @
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:
		
		/// <summary>
		/// Gets the first name of this Person (an example of a GETTER)
		/// </summary>
		/// <returns>the Person's first name</returns>
		std::string get_first_name();



		/// <summary>
		/// Gets the last name of this Person
		/// </summary>
		/// <returns>the Person's last name</returns>
		std::string get_last_name();



		/// <summary>
		/// Gets the ID of this Person
		/// </summary>
		/// <returns>the Person's id</returns>
		unsigned int get_id();



		/// <summary>
		/// Gets the hours this Person has worked this pay period
		/// </summary>
		/// <returns>the Person's hours worked</returns>
		int get_hours_worked();


		/// <summary>
		/// Gets the hourly rate for this Person
		/// </summary>
		/// <returns>hourly rate in dollars</returns>
		float get_rate();


		/// <summary>
		/// Sets the hours this Person has worked this pay period.  This is an 
		/// example of a SETTER.  Note, but not providing a setter for the other
		/// attributes we make them "read only"
		/// </summary>
		void set_hours_worked(int new_hours);
		


	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@ OTHER METHODS                   @
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:
		/// <summary>
		/// Compute the full-name of the person
		/// </summary>
		/// <param name="reversed">true if we want "Last, First" or false if we want "First Last"</param>
		/// <returns>The full computed name of this person</returns>
		std::string get_name(bool reversed = true);



		/// <summary>
		/// Computes the salary of this
		/// </summary>
		/// <param name="reset">Set to true if we want to reset the hours worked after calling this method</param>
		/// <returns></returns>
		float get_salary(bool reset = false);
	};
}
