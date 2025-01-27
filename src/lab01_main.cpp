#include <person.h>
#include <person_database.h>

int main(int argc, char** argv)
{
	// In this constructor, you'll read in the contents of the
	// text file into an array of Person objects. DO NOT use any
	// container types (std::vector, std::list, etc.)
	example::PersonDatabase PD("..\\..\\media\\persondb.txt");
}