#include <person.h> //why "" instead of <>??
#include <iostream>
#include <string.h>
#include <string>

Person::Person()
{
	id = -1;
	first_name = "?";
	last_name = "?";
	hourly_rate = 0.0f;
	hours_worked = 0;
}

Person::Person(int start_id, std::string start_fname, std::string start_lname)
{
	id = start_id;
	first_name = start_fname;
	last_name = start_lname;
	hourly_rate = 0.0f;
	hours_worked = 0;
}
Person::~Person()
{
	// We didn't allocate any resources so no code is necessary
	std::cout << "Person '" << first_name << " " << last_name << "' is about to die!\n";
}

int Person::get_id()
{
	return id;
}

std::string Person::get_first_name()
{
	return first_name;
}

std::string Person::get_last_name()
{
	return last_name;
}

float Person::get_hourly_rate()
{
	return hourly_rate;
}

unsigned int Person::get_hours_worked()
{
	return hours_worked;
}

void Person::set_hourly_rate(float new_rate)
{
	hourly_rate = new_rate;
}

void Person::set_hours_worked(unsigned int new_hours)
{
	hours_worked = new_hours;
}

//We're providing the BODY / DEFINITION of the method we declared in our h file
float Person::calculate_wage()
{
	//In any (non-static) method, we have access to all atrributes for this
	//instance. Our job in this method is to tell the compiler HOW to 
	//calculate a wage using our attributes
	return hourly_rate * hours_worked;
}