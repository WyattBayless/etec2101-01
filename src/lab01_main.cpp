#include <person.h>
#include <person_database.h>
#include <iostream>

int main(int argc, char** argv)
{
	// In this constructor, you'll read in the contents of the
	// text file into an array of Person objects. DO NOT use any
	// container types (std::vector, std::list, etc.)

	// Each person in persondb should have their own line, with information
	// in the order of ID number, First Name, Last Name, Hourly Rate, and then Hours worked.
	// Each element should be seperated by a comma
	example::PersonDatabase PD("..\\..\\media\\persondb.txt");
	example::Person person(1112, "Jane", "Doe");
	person.set_hourly_rate(11.6);
	person.set_hours_worked(38);
	PD.add_person(person);
}