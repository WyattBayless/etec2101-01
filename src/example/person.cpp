#include <person.h>

example::Person::Person()
{
	mFirstName = mLastName = "???";
	mID = 0;
	mHoursWorked = 0;
	mHourlyRate = 0.0f;
}



example::Person::~Person()
{
	// Nothing to do here...just a place-holder for the moment.
}



example::Person::Person(const std::string& starting_fname, const std::string& starting_lname, unsigned int id, float starting_rate) :
	mFirstName(starting_fname), mLastName(starting_lname), mID(id), mHourlyRate(starting_rate),
	mHoursWorked(0)
{
	// Note the alternate syntax used to initialize our attributes.  Sometimes this notation is necessary
	// since it assigns a value AS the attributes are created (the other version creates them, then
	// overwrites the values stored).  This method is usually faster.

	// Nothing to do here!
}

std::string example::Person::get_first_name()
{
	return mFirstName;
}

		

std::string example::Person::get_last_name()
{
	return mLastName;
}

	


unsigned int example::Person::get_id()
{
	return mID;
}


		
int example::Person::get_hours_worked()
{
	return mHoursWorked;
}



float example::Person::get_rate()
{
	return mHourlyRate;
}


		
void example::Person::set_hours_worked(int new_hours)
{
	mHoursWorked = new_hours;
}



// Note how you don't put the default value here (it's in the .h file)
std::string example::Person::get_name(bool reversed)
{
	if (reversed)
		return mLastName + ", " + mFirstName;
	else
		return mFirstName + " " + mLastName;
}



		
float example::Person::get_salary(bool reset)
{
	int h = mHoursWorked;
	if (reset)
		mHoursWorked = 0;
	return mHourlyRate * h;
}